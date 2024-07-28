#include "Miner.h"


unsigned long Miner::mineBlock(){
    uint32_t crc;
    bool hasLeadingZeros = false;
    BLOCK_T miner_block = block_to_be_mined;
    while (!hasLeadingZeros)
    {
        if (block_to_be_mined.height != miner_block.height){//check if there is a new block
            pthread_mutex_lock(&newBlockByServer_mutex);
            miner_block = block_to_be_mined;
            pthread_mutex_unlock(&newBlockByServer_mutex);
        }
        miner_block.relayed_by = id;
        crc = calculateCRC32(miner_block);
        hasLeadingZeros = hasLeadingZeroBits(crc,DIFFICULTY);
        if(hasLeadingZeros)
        {
            pthread_mutex_lock(&newBlockByServer_mutex);
            miner_block.hash = crc;
            mined_blocks.push(miner_block);
            relayMinedBlock(mined_blocks.back());
            pthread_mutex_unlock(&newBlockByServer_mutex);
        }
        miner_block.nonce++;
    }

    return crc;
}
unsigned long FakeMiner::mineBlock()
 {
    uint32_t crc;
    BLOCK_T miner_block = block_to_be_mined;
    while (true)
    {
        miner_block = block_to_be_mined;
        pthread_mutex_lock(&newBlockByServer_mutex);
        miner_block.relayed_by = id;
        crc = calculateCRC32(miner_block);
        miner_block.hash = crc;
        mined_blocks.push(miner_block);
        relayMinedBlock(mined_blocks.back());
        pthread_mutex_unlock(&newBlockByServer_mutex);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return crc;
}

void* Miner::start(void* arg) {
    BLOCK_T miner_block = block_to_be_mined;
    while (true){
        if (block_to_be_mined.height != miner_block.height){
            pthread_mutex_lock(&newBlockByServer_mutex);
            miner_block = block_to_be_mined;
            pthread_mutex_unlock(&newBlockByServer_mutex);
        }
        std::cout<<"s";

        mineBlock();
    }
    return nullptr;
}
void Miner::MinerBlockMessage(BLOCK_T block)
{
   std::cout<<typeid(*this).name() + 1<<"#"<<block.relayed_by << ": Mined a new block #"<<block.height<<" with hash 0x";//+1 to skip the number before the class name
   std::cout<<std::hex<<block.hash<<std::endl;
   std::cout<<std::dec;
}

void Miner::relayMinedBlock(BLOCK_T& block) {
    MinerBlockMessage(block);
    pthread_cond_signal(&block_hash_found);
}

