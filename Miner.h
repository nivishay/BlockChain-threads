#pragma once 
#include "BLOCK_T&Globals.h"

class Miner
{
    private:
    int id;
    pthread_t miner;

    //calculating the hash//
    unsigned long calculateCRC32(const BLOCK_T& block);
    bool hasLeadingZeroBits(unsigned int number, int x);
    int countLeadingZeros(unsigned int number);

    static void* minerThreadWrapper(void* miner_id);

    public:
    void* miner_thread(void* miner_id);
    virtual unsigned long mineBlock(BLOCK_T& block,int difficulty);

    Miner(int id):id(id) {
        pthread_create(&miner, nullptr, &Miner::minerThreadWrapper,&id);
    }
    void join() {
        pthread_join(id,nullptr);
    }
    Miner(int id):id(id) {

    }
    void start(BLOCK_T& block);
    void MinerBlockMessage(BLOCK_T block);

    ~Miner() = default;
};
class FakeMiner : public Miner
{
    public:
    unsigned long mineBlock(BLOCK_T& block,int difficulty) override;
};

