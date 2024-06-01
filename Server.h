#ifndef SERVER_H
#define SERVER_H
#include "BLOCK_T&Globals.h"
#include <iostream>
#include <list>

class Server
{
private:
    std::list<BLOCK_T> blockChain;
    std::thread server_t;//server thread
     void ServerBlockMessage(BLOCK_T block);
public:
     Server();

    void join() 
    {
        if(server_t.joinable())
        {
            std::cout<<"Server joined"<<std::endl;
            server_t.join();
        }
    }
    void addBlock(BLOCK_T block);
    void* start(void* arg);
};

#endif // SERVER_H