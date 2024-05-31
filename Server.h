#pragma once

#include "BLOCK_T&Globals.h"
#include <iostream>
#include <list>

class Server
{
private:
    std::list<BLOCK_T> blockChain;
    pthread_t server_t;//server thread
    static void* ServerWrapper(void* server_id);
     void ServerBlockMessage(BLOCK_T block);
public:
     void* server_thread(void* server_id);
     Server();

    void join() 
    {
    pthread_join(server_t,nullptr);//join server thread
    }
    void addBlock(BLOCK_T block);
    void start(BLOCK_T& block);
};