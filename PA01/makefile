CC = g++
FLAGS = -Wall -g -std=c++11

all: PA01.o PrecondViolatedExcept.o
	$(CC) $(FLAGS) PA01.o PrecondViolatedExcept.o -o PA01

PA01.o: PA01.cpp
	$(CC) $(FLAGS) -c PA01.cpp
	
PA01.cpp: LinkedList.h

LinkedList.h: ListInterface.h Node.h PrecondViolatedExcept.h LinkedList.cpp

Node.h: Node.cpp

PrecondViolatedExcept.o: PrecondViolatedExcept.cpp
	$(CC) $(FLAGS) -c PrecondViolatedExcept.cpp
	
PrecondViolatedExcept.cpp: PrecondViolatedExcept.h
