CC=g++
MAIN=./test.cpp
BINARY=./prog
VALGRIND=valgrind --leak-check=full

SOURCE=../src/backend/rng.cpp \
       ../src/backend/skills.cpp \
       ../src/backend/liesel.cpp \
       ../src/backend/enemy.cpp \

INCLUDE=..

all:

	$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I$(INCLUDE)

run:

	$(BINARY)

valgrind:

	$(CC) $(MAIN) $(SOURCE) -g -o $(BINARY) -I$(INCLUDE)
	$(VALGRIND) $(BINARY)
