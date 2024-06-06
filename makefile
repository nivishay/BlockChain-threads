CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lz

all: main Miner Server BLOCK_T&Globals

BLOCK_T&Globals: BLOCK_T&Globals.o
	$(CC) $(CFLAGS) BLOCK_T&Globals.o -o BLOCK_T&Globals $(LDFLAGS)
Server: Server.o
	$(CC) $(CFLAGS) Server.o -o Server $(LDFLAGS)
Miner: Miner.o
	$(CC) $(CFLAGS) Miner.o -o Miner $(LDFLAGS)
main: main.o
	$(CC) $(CFLAGS) main.o -o main $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Miner.o: Miner.cpp
	$(CC) $(CFLAGS) -c Miner.cpp

Server.o: Server.cpp
	$(CC) $(CFLAGS) -c Server.cpp

BLOCK_T&Globals.o: BLOCK_T&Globals.cpp
	$(CC) $(CFLAGS) -c BLOCK_T&Globals.cpp

clean:
	rm -f main.o main Miner.o Miner Server.o Server