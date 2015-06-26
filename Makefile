CXX=clang++
CXXFLAGS=-I. -std=c++11 -Wall -pedantic
.PHONY: clean

all: objects tests

objects: neuron.o

tests: sigmoid_neuron_test test
	$(CXX) $(CXXFLAGS) -lgtest sigmoid_neuron_test.o test.o -o test

test: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

neuron.o: neuron.cpp neuron.h
	$(CXX) $(CXXFLAGS) -c neuron.cpp -o neuron.o

sigmoid_neuron_test: sigmoid_neuron_test.h sigmoid_neuron_test.cpp sigmoid_neuron.o neuron.o
	$(CXX) $(CXXFLAGS) -c sigmoid_neuron_test.cpp -o sigmoid_neuron_test.o

clean:
	rm *.o
