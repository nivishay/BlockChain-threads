#include "BLOCK_T&Globals.h"
#include "Miner.h"
#include "Server.h"

int main(int argc, char* argv[])
{
    //TODO:chage the +1
    std::vector<Miner> miner_threads(NUM_MINERS+1);//vector of miner threads
    Server server;
    pthread_cond_init(&block_hash_found, NULL);
    pthread_cond_init(&newBlockByServer, NULL);
    
    for (int i = 0; i < NUM_MINERS; i++) {//create miner threads
        miner_threads[i] = Miner(i+1);
        miner_threads[i].start();
    }
       for (int i = 0; i < NUM_MINERS; i++) {//create miner threads
        miner_threads[i].join();
    }
    server.start();
    server.join();
    return 0;
}
