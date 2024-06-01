# funCoin

## Objective
The objective of this project is to practice synchronization between consumer and producer threads within the same process. This is achieved by executing a multithreaded application that simulates a cryptocurrency blockchain network with 4 mining threads and 1 server thread.

## Blockchain Overview
A blockchain is a growing list of records, called blocks, that are linked using cryptography. Each block contains a cryptographic hash of the previous block, a timestamp, and transaction data. For more details, see the [Wikipedia article on Blockchain](https://en.wikipedia.org/wiki/Blockchain).

### Cryptographic Hash
A cryptographic hash is an algorithm that can be run on data (a block in this case) to produce an irreversible and unique (almost) checksum. Typically, SHA256 is used, but in this project, we will use a simple checksum function, CRC32, which is part of the zlib library. Learn more about CRC32 [here](https://en.wikipedia.org/wiki/Cyclic_redundancy_check).

### Mining
Mining involves calculating a hash (checksum) on a given block and appending it to the end of the blockchain once found. This block is then propagated to other miners.

### Proof of Work
Proof of Work (PoW) is a piece of data that is difficult and time-consuming to produce but easy for others to verify. It satisfies certain requirements, often involving numerous trials and errors before a valid PoW is generated. Bitcoin, for example, requires miners to find a hash with a specific number of leading zeros. In this project, we use CRC32 and check for leading zero bits.

## Assignment Description
This project involves writing a C/C++ program divided into 4 miner threads and 1 server thread.
## this project uses
Multithreading: Implementing and managing multiple threads for simultaneous mining and server verification.

Synchronization: Techniques for synchronizing consumer and producer threads to ensure smooth operation.

Blockchain Concepts: Understanding and applying blockchain principles such as cryptographic hashing, mining, and proof-of-work.

C++ Polymorphism : Using polymorphism to create flexible and reusable code components.

Code Organization: Structuring a project hierarchically to improve readability and maintainability.

### Block Structure
```c
typedef struct {
    int             height;        // Incremental ID of the block in the chain
    int             timestamp;     // Time of the mine in seconds since epoch
    unsigned int    hash;          // Current block hash value
    unsigned int    prev_hash;     // Hash value of the previous block
    int             difficulty;    // Amount of preceding zeros in the hash
    int             nonce;         // Incremental integer to change the hash value
    int             relayed_by;    // Miner ID
} BLOCK_T;


