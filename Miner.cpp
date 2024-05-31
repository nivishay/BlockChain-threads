#include "Miner.h"

void* Miner::minerThreadWrapper(void* miner_id) {
    Miner* miner = static_cast<Miner*>(miner_id);
    return miner->start();
}
int Miner::countLeadingZeros(unsigned int number) {
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
bool Miner::hasLeadingZeroBits(unsigned int number, int x) {
    return countLeadingZeros(number) == x;
}

unsigned long Miner::mineBlock(BLOCK_T& block,int difficulty) {
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
unsigned long FakeMiner::mineBlock(BLOCK_T& block,int difficulty) {
    uint32_t crc;
    return crc = calculateCRC32(block);
}

void* Miner::start(){
        while (true){
        pthread_mutex_lock(&newBlockByServer_mutex);
        pthread_cond_wait(&newBlockByServer, &newBlockByServer_mutex);
        block_to_be_mined.hash = mineBlock(block_to_be_mined, block_to_be_mined.difficulty);
        block_to_be_mined.relayed_by = id;
        MinerBlockMessage(block_to_be_mined);
        //UNLOCK
        pthread_cond_signal(&block_hash_found);
    }
}
void Miner::MinerBlockMessage(BLOCK_T block)
{
   std::cout<<"Miner #"<<block.relayed_by << ": Mined a new block #"<<block.height<<" with hash 0x"<<std::hex<<block.hash<<std::endl;//TODO:change hex to dec
}

