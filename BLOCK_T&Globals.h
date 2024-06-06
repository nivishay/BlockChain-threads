#ifndef _WIN32
#define _WIN32

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <zlib.h>
#include <list>
#include <ctime>
#include <pthread.h>
#include <iomanip>
#include <queue>

 typedef struct {
    int         	height;        // Incrementeal ID of the block in the chain
    int         	timestamp;    // Time of the mine in seconds since epoch
    unsigned int    hash;        // Current block hash value
    unsigned int    prev_hash;    // Hash value of the previous block
    int        	difficulty;    // Amount of preceding zeros in the hash
    int         	nonce;        // Incremental integer to change the hash value
    int         	relayed_by;    // Miner ID
 }BLOCK_T;

extern std::queue <BLOCK_T> mined_blocks;
extern unsigned int hash_found;        // Current block hash value
extern BLOCK_T block_to_be_mined;
extern pthread_cond_t block_hash_found;
extern pthread_mutex_t block_hash_found_mutex;

extern pthread_cond_t newBlockByServer;
extern pthread_mutex_t newBlockByServer_mutex;
#define FAKE_MINER_ID 1
#define NUM_MINERS 5
extern int  DIFFICULTY;//TODO:needs to be argv from the program

bool hasLeadingZeroBits(unsigned int number, int x);
int countLeadingZeros(unsigned int number);
unsigned long calculateCRC32(const BLOCK_T& block);

#endif //_WIN32