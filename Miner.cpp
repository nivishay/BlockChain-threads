#include "Miner.h"

unsigned long Miner::mineBlock(BLOCK_T& block,int difficulty) {//TODO:no need for the parameters
    uint32_t crc;
    bool hasLeadingZeros = false;
    while (!hasLeadingZeros) {
        pthread_mutex_lock(&newBlockByServer_mutex);
        block_to_be_mined.relayed_by = id;
        crc = calculateCRC32(block_to_be_mined);
        hasLeadingZeros = hasLeadingZeroBits(crc,difficulty);
        if(hasLeadingZeros)
        {
            block_to_be_mined.hash = crc;
            relayMinedBlock();
        }
        block.nonce++;
        pthread_mutex_unlock(&newBlockByServer_mutex);
    }

    return crc;
}
unsigned long FakeMiner::mineBlock(BLOCK_T& block,int difficulty) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    uint32_t crc;
    return crc = calculateCRC32(block);
}
void* Miner::start(void* arg) {
        while (true){
        pthread_mutex_lock(&newBlockByServer_mutex);
        pthread_cond_wait(&newBlockByServer, &newBlockByServer_mutex);
        pthread_mutex_unlock(&newBlockByServer_mutex);
        mineBlock(block_to_be_mined, block_to_be_mined.difficulty);
    }
    return nullptr;
}
void Miner::MinerBlockMessage(BLOCK_T block)
{
   std::cout<<"Miner #"<<block.relayed_by << ": Mined a new block #"<<block.height<<" with hash 0x";
   std::cout<<std::hex<<block.hash<<std::endl;
   std::cout<<std::dec;
}

void Miner::relayMinedBlock() {
    MinerBlockMessage(block_to_be_mined);
    pthread_cond_signal(&block_hash_found);
}
