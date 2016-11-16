CXX = g++
CXXFLAGS = -Wall -std=c++11

SRCS = PA05.cpp ABEventQueue.cpp LLEventQueue.cpp EventQueue.cpp TellerSetup.cpp TellerSetup_1QnT.cpp TellerSetup_nQnT.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = PA05

.PHONY: clean

all: $(MAIN)
	@echo Compilation successful!
	
$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

%.o: %.c
	$(CXX) -c $(CXXFLAGS) -c $< -o $@
	
clean:
	rm *.o
	rm $(MAIN)