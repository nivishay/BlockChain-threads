#ifndef MINER_H
#define MINER_H
#include "BLOCK_T&Globals.h"
class Miner
{
    protected:
    int id;
    private:
    BLOCK_T myBlock;
    std::thread miner;

    //calculating the hash//
    public:
   void  changeWorkingBlock(BLOCK_T b){
        myBlock =b;
    }
    BLOCK_T getWorkingBlock()
    {
        return myBlock;
    }

    virtual unsigned long mineBlock();
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
    void relayMinedBlock(BLOCK_T& block);

    ~Miner()
    {
        join();
    }

};
class FakeMiner : public Miner
{
    public:
        FakeMiner(int id):Miner(id){}
    
    unsigned long mineBlock() override;
};


#endif // MINER_H
