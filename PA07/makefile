CXX := g++
CXXFLAGS := -Wall -std=c++11

SRCS := $(shell find . -name '.cpp')
HDRS := $(shell find . -name '.h')s
OBJS := $(SRCS:.cpp=.o)
MAIN := $(shell pwd | sed -r 's/.*\/(.*)$/\1/')

.PHONY: all build clean doxygen zip run

build: $(MAIN)
	@echo Compilation successful!

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -rf latex/
	rm -rf $(MAIN)_MatthewBauer

doxygen:
	doxygen .
	make --directory=latex/
	cp latex/refman.pdf $(MAIN).pdf

zip:
	mkdir $(MAIN)_MatthewBauer
	cp $(SRCS) $(HDRS) $(MAIN).pdf makefile $(MAIN)_MatthewBauer/
	cp out.txt $(MAIN)_MatthewBauer/
	rm -f $(MAIN)_MatthewBauer.zip
	zip -r $(MAIN)_MatthewBauer $(MAIN)_MatthewBauer

run:
	./$(MAIN) > out.txt

all: build doxygen run zip
