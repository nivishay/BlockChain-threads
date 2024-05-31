#include "Miner.h"

void* Miner::minerThreadWrapper(void* miner_id) {

    Miner* miner = static_cast<Miner*>(miner_id);
    return miner->miner_thread(miner_id); 
}


