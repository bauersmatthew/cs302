CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = PA06.cpp BinSearchTree.cpp BSTOStream.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = PA06

.PHONY: clean
.PHONY: doxygen

all: $(MAIN)
	@echo Compilation successful!

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	rm *.o
	rm -rf latex/
	
doxygen:
	doxygen .
	make --directory=latex/
	cp latex/refman.pdf $(MAIN).pdf
