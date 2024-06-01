#ifndef MINER_H
#define MINER_H
#include "BLOCK_T&Globals.h"

class Miner
{
    private:
    int id;
    std::thread miner;

    //calculating the hash//
    bool hasLeadingZeroBits(unsigned int number, int x);
    int countLeadingZeros(unsigned int number);

    protected:
    unsigned long calculateCRC32(const BLOCK_T& block);
    
    public:
    virtual unsigned long mineBlock(BLOCK_T& block,int difficulty);
    Miner() = default;
    Miner(int id):id(id)
    {
        miner = std::thread(&Miner::start,this,nullptr);
    }

    void join() 
    {
        if(miner.joinable())
            miner.join();
    }
    
    void* start(void* arg);
    void MinerBlockMessage(BLOCK_T block);

    ~Miner()
    {
        join();
    }
};
class FakeMiner : public Miner
{
    public:
    unsigned long mineBlock(BLOCK_T& block,int difficulty) override;
};

#endif // MINER_H
