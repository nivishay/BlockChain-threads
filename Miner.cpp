#include "Miner.h"


unsigned long Miner::mineBlock(){//TODO:no need for the parameters
    uint32_t crc;
    bool hasLeadingZeros = false;
    BLOCK_T miner_block = block_to_be_mined;
    while (!hasLeadingZeros)
    {
        pthread_mutex_lock(&newBlockByServer_mutex);
        miner_block.relayed_by = id;
        crc = calculateCRC32(miner_block);
        hasLeadingZeros = hasLeadingZeroBits(crc,DIFFICULTY);
        if(hasLeadingZeros)
        {
            hash_found = crc;
            mined_block = miner_block;
            relayMinedBlock(mined_block);
        }
        miner_block.nonce++;
        pthread_mutex_unlock(&newBlockByServer_mutex);
    }

    return crc;
}
unsigned long FakeMiner::mineBlock()
 {
    BLOCK_T block = block_to_be_mined;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    uint32_t crc;
    return crc = calculateCRC32(block);
}

void* Miner::start(void* arg) {
        while (true){
        pthread_mutex_lock(&newBlockByServer_mutex);
        pthread_cond_wait(&newBlockByServer, &newBlockByServer_mutex);
        pthread_mutex_unlock(&newBlockByServer_mutex);
        mineBlock();
    }
    return nullptr;
}
void Miner::MinerBlockMessage(BLOCK_T block)
{
   std::cout<<"Miner #"<<block.relayed_by << ": Mined a new block #"<<block.height<<" with hash 0x";
   std::cout<<std::hex<<hash_found<<std::endl;
   std::cout<<std::dec;
}

void Miner::relayMinedBlock(BLOCK_T& block) {
    MinerBlockMessage(block);
    pthread_cond_signal(&block_hash_found);
}

