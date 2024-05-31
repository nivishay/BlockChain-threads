CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lz

all: main

main: main.o
	$(CC) $(CFLAGS) main.o -o main $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
clean:
	rm -f main.o main