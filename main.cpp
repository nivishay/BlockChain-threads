#include "Miner.h"
#include "Server.h"


 pthread_cond_t block_hash_found = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t block_hash_found_mutex = PTHREAD_MUTEX_INITIALIZER;

 pthread_cond_t newBlockByServer = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t newBlockByServer_mutex = PTHREAD_MUTEX_INITIALIZER;
 BLOCK_T block_to_be_mined = {1, static_cast<int>(time(nullptr)),0, 0, DIFFICULTY, 0, -1};
 BLOCK_T mined_block;
 int  DIFFICULTY = 10;
 unsigned int hash_found = 0;     // Current block hash value
 std::queue <BLOCK_T> mined_blocks;

 
int main(int argc, char* argv[])
{
    std::cout << "Enter difficulty: ";
    std::cin >> DIFFICULTY;
    std::vector<Miner*> miner_threads(NUM_MINERS);//vector of miner threads
    for (int i = 1; i < NUM_MINERS; i++) 
        miner_threads[i] = new Miner(i);//TODO:needs to add the fake Miner

    miner_threads.push_back(new FakeMiner(FAKE_MINER_ID));//TODO:needs to add the fake Miner

    Server server;
    return 0;
}
