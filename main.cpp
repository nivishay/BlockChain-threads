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


