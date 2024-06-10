#include "Server.h"

Server::Server()
 {
    pthread_attr_t attr; // Thread attributes
    struct sched_param param; // Scheduling parameters
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    param.sched_priority = 10; // Set priority to 10 (you can choose any value within the priority range)
    pthread_attr_setschedparam(&attr, &param);
    server_t = std::thread(&Server::start,this,nullptr);
}

void Server::addBlock(BLOCK_T block)
 {
    blockChain.push_back(block);
    ServerBlockMessage(block); 
}

void Server::ServerBlockMessage(BLOCK_T block)
 {
    std::cout<<"Server: new block added by "<<block.relayed_by<<" attributes: height ("<<block.height<<"), Timestamp("<<block.timestamp<<"), hash (0x";
    std::cout<<std::hex<<block.hash<<"), prev_hash(0x"<<std::hex<<block.prev_hash<<"), difficulty (";
    std::cout<<std::dec<<block.difficulty<<"), nonce ("<<block.nonce<<")"<<std::endl;
}

bool Server::isValidHash(BLOCK_T block) 
{
    int hash =block.hash;
    block.hash = 0;
    if(hash == calculateCRC32(block)&&hasLeadingZeroBits(hash,DIFFICULTY))
    {
        block.hash = hash;
        return true;
    }
    block.hash = hash;
    return false;
}

void* Server::start(void* arg)
 {
    while (true) {
        pthread_cond_broadcast(&newBlockByServer);//notify the miners that a new block is found
        pthread_mutex_lock(&block_hash_found_mutex);
        pthread_cond_wait(&block_hash_found, &block_hash_found_mutex);
        while(!mined_blocks.empty())
        {
            BLOCK_T current_block = mined_blocks.front();
            mined_blocks.pop();
            
        if(!isValidHash(current_block)) 
        {
            std::cout<<"Server: invalid hash, block: ";
            std::cout<<std::hex<<current_block.hash;
            std::cout<<std::endl;
            std::cout<<std::dec;
        }
        else if(current_block.height > blockChain.back().height)// block not mined yet(meaning +1 in height)
        {
            addBlock(current_block);
            sleep(1);
            block_to_be_mined = {blockChain.back().height + 1,static_cast<int>(time(nullptr)), 0,blockChain.back().hash, DIFFICULTY,1, -1};
        }
        else
        {
            std::cout<<"Server: block: #";
            std::cout<<current_block.height;
            std::cout<<" already mined, block with hash: 0x";
            std::cout<<std::hex<<current_block.hash;
            std::cout<<std::dec;
            std::cout<<" not added"<<std::endl;
        }
        }
        pthread_mutex_unlock(&block_hash_found_mutex);
    }
    return nullptr;
}
