CC = g++
FLAGS = -Wall -g -std=c++11

all: PA03.o FlightMap.v2.o
	$(CC) $(FLAGS) PA03.o FlightMap.v2.o -o PA03

PA03.o: PA03.cpp
	$(CC) $(FLAGS) -c PA03.cpp

PA03.cpp: FlightMap.v2.h

FlightMap.v2.h: FlightMap.v2.cpp
	$(CC) $(FLAGS) -c FlightMap.v2.cpp

FlightMap.v2.o: FlightMap.v2.cpp
	$(CC) $(FLAGS) -c FlightMap.v2.cpp