#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <zlib.h>
#include <ctime>
#include <list>
#include <pthread.h>
#include <iomanip>

#define NUM_MINERS 4
#define DIFFICULTY 23

pthread_cond_t block_hash_found = PTHREAD_COND_INITIALIZER;
pthread_mutex_t block_hash_found_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t newBlockByServer = PTHREAD_COND_INITIALIZER;
pthread_mutex_t newBlockByServer_mutex = PTHREAD_MUTEX_INITIALIZER;

 typedef struct {
    int         	height;        // Incrementeal ID of the block in the chain
    int         	timestamp;    // Time of the mine in seconds since epoch
    unsigned int    hash;        // Current block hash value
    unsigned int    prev_hash;    // Hash value of the previous block
    int        	difficulty;    // Amount of preceding zeros in the hash
    int         	nonce;        // Incremental integer to change the hash value
    int         	relayed_by;    // Miner ID
 } BLOCK_T;
 

std::list<BLOCK_T> blockChain;//
BLOCK_T block_to_be_mined;

//miner functions//
void* miner_thread(void* miner_id);
unsigned long calculateCRC32(const BLOCK_T& block);
bool hasLeadingZeroBits(unsigned int number, int x);
int countLeadingZeros(unsigned int number);
unsigned long mineBlock(BLOCK_T& block,int difficulty);


//SERVER FUNCTIONS//
void* server_thread(void* server_id);
void ServerBlockMessage(BLOCK_T block);
void MinerBlockMessage(BLOCK_T block);

int main(int argc, char* argv[])
{
    std::vector<pthread_t> miner_threads_id(NUM_MINERS+1);//vector of miner threads 

    pthread_t server_t;//server thread
    pthread_attr_t attr; // Thread attributes
    struct sched_param param; // Scheduling parameters
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    param.sched_priority = 10; // Set priority to 10 (you can choose any value within the priority range)
    pthread_attr_setschedparam(&attr, &param);

    pthread_cond_init(&block_hash_found, NULL);
    pthread_cond_init(&newBlockByServer, NULL);
    int miner_id;
    pthread_t miner;
    for (int i = 0; i < NUM_MINERS; i++) {//create miner threads

        miner_id = i+1;
        miner = miner_threads_id[i];
        pthread_create(&miner, nullptr, miner_thread,&miner_id);
    }

        for (int i = 0; i < NUM_MINERS; i++) {
        pthread_join(miner_threads_id[i], nullptr);
    }

    pthread_create(&server_t,&attr,server_thread, nullptr);//create server thread

    pthread_join(server_t, nullptr);//join server thread
    
    return 0;
}

void* miner_thread(void* miner_id)
{
    int id = *(int*)miner_id;
    while (true){
        pthread_mutex_lock(&newBlockByServer_mutex);
        pthread_cond_wait(&newBlockByServer, &newBlockByServer_mutex);
        block_to_be_mined.hash = mineBlock(block_to_be_mined, block_to_be_mined.difficulty);
        block_to_be_mined.relayed_by = id;
        MinerBlockMessage(block_to_be_mined);
        //UNLOCK
        pthread_cond_signal(&block_hash_found);
    }
    return nullptr;
}
void* server_thread(void* server_id)
{
    block_to_be_mined = {1, static_cast<int>(time(nullptr)), 0, 0, DIFFICULTY, 0, -1}; // TODO: CHANGE PRIORTY TO BE HIGHT THEN MINERS
    while (true) {
        pthread_cond_broadcast(&newBlockByServer);//notify the miners that a new block is found
        pthread_mutex_lock(&block_hash_found_mutex);
        pthread_cond_wait(&block_hash_found, &block_hash_found_mutex);
        ServerBlockMessage(block_to_be_mined);
        blockChain.push_back(block_to_be_mined);
        sleep(2);
        block_to_be_mined = {block_to_be_mined.height + 1,static_cast<int>(time(nullptr)), 0,blockChain.back().hash, DIFFICULTY,1, -1};
        pthread_mutex_unlock(&block_hash_found_mutex);

    }
    return 0;
}
void ServerBlockMessage(BLOCK_T block) {
    std::cout<<"Server: new block added by "<<block_to_be_mined.relayed_by<<" attributes: ("<<block_to_be_mined.height<<"), Timestamp("<<block_to_be_mined.timestamp<<"), hash (0x"<<std::hex<<block_to_be_mined.hash<<"), prev_hash(0x"<<std::hex<<block_to_be_mined.prev_hash<<"), difficulty ("<<block_to_be_mined.difficulty<<"), nonce ("<<block_to_be_mined.nonce<<")"<<std::endl;
}
void MinerBlockMessage(BLOCK_T block)
{
   std::cout<<"Miner #"<<block_to_be_mined.relayed_by << ": Mined a new block #"<<block_to_be_mined.height<<" with hash 0x"<<std::hex<<block_to_be_mined.hash<<std::endl;

}
//FUNCTIONS FOR CALCULATING THE HASH//
/////////////////////////////////////
unsigned long calculateCRC32(const BLOCK_T& block) {
    unsigned long crc = crc32(0, nullptr, 0);
    crc = crc32(crc, reinterpret_cast<const Bytef*>(&block), sizeof(block));
    return crc;
}

// Function to count leading zero bits
int countLeadingZeros(unsigned int number) {
    int leadingZeros = 0;
    for (int i = 31; i >= 0; --i) {
        if ((number & (1U << i)) == 0) {
            leadingZeros++;
        } else {
            break;
        }
    }
    return leadingZeros;
}
// Function to check if the number has exactly x leading zero bits
bool hasLeadingZeroBits(unsigned int number, int x) {
    return countLeadingZeros(number) == x;
}

unsigned long mineBlock(BLOCK_T& block,int difficulty) {
    uint32_t crc;
    bool hasLeadingZeros = false;
    while (!hasLeadingZeros) {
        crc = calculateCRC32(block);
        block.nonce++;
        hasLeadingZeros = hasLeadingZeroBits(crc,difficulty);
    }
    pthread_mutex_unlock(&newBlockByServer_mutex);
    return crc;
}

