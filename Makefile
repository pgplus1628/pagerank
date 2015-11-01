CXX?=g++
CXXFLAGS?=-std=c++11 -g -O3
LDFLAGS?=-L/usr/local/lib -lglog -lgflags -lm
INFLAGS?=-I. -I/usr/local/include/ -I/usr/include/ 

all : pagerank


pagerank : pagerank.o order.o graph.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

pagerank.o : pagerank.cpp
	$(CXX) $(CXXFLAGS) $(INFLAGS) -c $< -o $@

graph.o : graph.cpp
	$(CXX) $(CXXFLAGS) $(INFLAGS) -c $< -o $@

order.o : order.cpp
	$(CXX) $(CXXFLAGS) $(INFLAGS) -c $< -o $@


.PHONY:

clean :
	rm -f *.o
	rm -f pagerank
