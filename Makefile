CXX=clang++
CXXFLAGS=-I. -std=c++11 -Wall -pedantic
.PHONY: clean

all: objects

objects: neuron.o

neuron.o: neuron.cpp neuron.h
	$(CXX) $(CXXFLAGS) -c neuron.cpp -o neuron.o

clean:
	rm *.o
