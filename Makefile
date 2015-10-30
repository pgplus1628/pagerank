CXX?=g++
CXXFLAGS?=-std=c++11 -g
LDFLAGS?=-L/usr/local/lib/ -lglog -lgflags
INFLAGS?=-I. -I/usr/local/include/

all : pagerank

pagerank : pagerank.o
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

pagerank.o : pagerank.cpp
	$(CXX) $(CXXFLAGS) $(INFLAGS) -c $< -o $@

.PHONY:

clean :
	rm -f pagerank.o
	rm -f pagerank