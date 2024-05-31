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

 typedef struct {
    int         	height;        // Incrementeal ID of the block in the chain
    int         	timestamp;    // Time of the mine in seconds since epoch
    unsigned int    hash;        // Current block hash value
    unsigned int    prev_hash;    // Hash value of the previous block
    int        	difficulty;    // Amount of preceding zeros in the hash
    int         	nonce;        // Incremental integer to change the hash value
    int         	relayed_by;    // Miner ID
 }BLOCK_T;

#define NUM_MINERS 4
#define DIFFICULTY 23

BLOCK_T block_to_be_mined;
pthread_cond_t block_hash_found = PTHREAD_COND_INITIALIZER;
pthread_mutex_t block_hash_found_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t newBlockByServer = PTHREAD_COND_INITIALIZER;
pthread_mutex_t newBlockByServer_mutex = PTHREAD_MUTEX_INITIALIZER;

#endif //_WIN32