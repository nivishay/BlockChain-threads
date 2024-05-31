#ifndef MINER_H
#define MINER_H
#include "BLOCK_T&Globals.h"

class Miner
{
    private:
    int id;
    pthread_t miner;

    //calculating the hash//
    bool hasLeadingZeroBits(unsigned int number, int x);
    int countLeadingZeros(unsigned int number);

    static void* minerThreadWrapper(void* miner_id);

    protected:
    unsigned long calculateCRC32(const BLOCK_T& block);
    
    public:
    virtual unsigned long mineBlock(BLOCK_T& block,int difficulty);
    Miner() = default;
    Miner(int id):id(id) {
        pthread_create(&miner, nullptr, &Miner::minerThreadWrapper,&id);
    }
    void join() {
        pthread_join(id,nullptr);
    }
    void* start();
    void MinerBlockMessage(BLOCK_T block);

    ~Miner() = default;
};
class FakeMiner : public Miner
{
    public:
    unsigned long mineBlock(BLOCK_T& block,int difficulty) override;
};


#endif // MINER_H
