#pragma once 
#include <iostream>
class BLOCK_T;
class Miner
{
    private:
    int id;
    pthread_t miner;

    //calculating the hash//
    unsigned long calculateCRC32(const BLOCK_T& block);
    bool hasLeadingZeroBits(unsigned int number, int x);
    int countLeadingZeros(unsigned int number);
    
    public:
    void* miner_thread(void* miner_id);
    virtual unsigned long mineBlock(BLOCK_T& block,int difficulty);
    static void* minerThreadWrapper(void* miner_id);
    Miner(int id):id(id) {
        pthread_create(&miner, nullptr, &Miner::minerThreadWrapper, this);
    }
    Miner(int id):id(id) {

    }
    ~Miner() = default;
};

class FakeMiner : public Miner
{
    public:
    unsigned long mineBlock(BLOCK_T& block,int difficulty) override;
};

