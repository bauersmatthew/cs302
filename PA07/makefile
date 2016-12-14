CXX := g++
CXXFLAGS := -Wall -std=c++11

SRCS := $(shell find . -name '*.cpp')
HDRS := $(shell find . -name '*.h')
OBJS := $(SRCS:.cpp=.o)
MAIN := $(notdir $(shell pwd))

.PHONY: all build clean doxygen zip run

build: $(MAIN)
	@echo $(MAIN)
	@echo $(HDRS)
	@echo $(SRCS)
	@echo $(OBJS)
	@echo Compilation successful!

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -rf latex/
	rm -rf html/
	rm -rf $(MAIN)_MatthewBauer
	rm -f Doxyfile

doxygen: Doxyfile
	doxygen .
	rm -rf html/
	make --directory=latex/
	cp latex/refman.pdf $(MAIN).pdf

Doxyfile:
	doxygen -g doxyt0
	sed -r 's/^PROJECT_NAME.*$/PROJECT_NAME = "$(MAIN)"/' < doxyt0 > doxyt1
	sed -r 's/^EXTRACT_ALL.*$/EXTRACT_ALL = YES/' < doxyt1 > doxyt2
	sed -r 's/^EXTRACT_PRIVATE.*$/EXTRACT_PRIVATE = YES/' < doxyt2 > doxyt3
	sed -r 's/^GENERATE_HTML.*$/GENERATE_HTML = NO/' < doxyt3 > Doxyfile
	rm -f doxyt*

zip:
	mkdir $(MAIN)_MatthewBauer
	cp $(SRCS) $(HDRS) $(MAIN).pdf makefile $(MAIN)_MatthewBauer/
	cp out.txt $(MAIN)_MatthewBauer/
	rm -f $(MAIN)_MatthewBauer.zip
	zip -r $(MAIN)_MatthewBauer $(MAIN)_MatthewBauer

run:
	./$(MAIN) > out.txt

all: build doxygen run zip
