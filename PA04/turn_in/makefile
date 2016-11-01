CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = PA04.cpp Sorter.cpp BubbleSorter.cpp CountingSorter.cpp MergeSorter.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = PA04

.PHONY: clean

all: $(MAIN)
	@echo Compilation successful!
	
$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) -c $< -o $@
	
clean:
	rm *.o
	rm PA04
