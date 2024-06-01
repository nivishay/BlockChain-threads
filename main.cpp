#include "Miner.h"
#include "Server.h"

 pthread_cond_t block_hash_found = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t block_hash_found_mutex = PTHREAD_MUTEX_INITIALIZER;

 pthread_cond_t newBlockByServer = PTHREAD_COND_INITIALIZER;
 pthread_mutex_t newBlockByServer_mutex = PTHREAD_MUTEX_INITIALIZER;
 
 BLOCK_T block_to_be_mined = {1, static_cast<int>(time(nullptr)), 0, 0, DIFFICULTY, 0, -1};
 using namespace std;
 
 
int main(int argc, char* argv[])
{
    //TODO:chage the +1
    std::vector<Miner*> miner_threads(NUM_MINERS+1);//vector of miner threads

    pthread_cond_init(&block_hash_found, NULL);
    pthread_cond_init(&newBlockByServer, NULL);
    
    for (int i = 0; i < NUM_MINERS; i++) {//create miner threads
        miner_threads[i] = new Miner(i+1);
    }
    Server server;
    return 0;
}
