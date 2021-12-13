CC=g++
MAIN=./test.cpp
BINARY=./prog
VALGRIND=valgrind --leak-check=full

SOURCE=../src/backend/*.cpp
INCLUDE=..

all:

	$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I$(INCLUDE)

run:

	$(BINARY)

valgrind:

	$(CC) $(MAIN) $(SOURCE) -g -o $(BINARY) -I$(INCLUDE)
	$(VALGRIND) $(BINARY)
