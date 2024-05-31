CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lz

all: main miner server

main: main.o
	$(CC) $(CFLAGS) main.o -o main $(LDFLAGS)

miner: miner.o
	$(CC) $(CFLAGS) miner.o -o miner $(LDFLAGS)

server: server.o
	$(CC) $(CFLAGS) server.o -o server $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

miner.o: miner.cpp
	$(CC) $(CFLAGS) -c miner.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

clean:
	rm -f main.o main miner.o miner server.o server