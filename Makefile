# General settings
CXX := g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++14 -ggdb3 -march=native -I$(SRCDIR)

# Define src, obj, bin and test dirs inside basedir
BASEDIR := .
SRCDIR := $(BASEDIR)/src
OBJDIR := $(BASEDIR)/obj
BINDIR := $(BASEDIR)/bin
TESTDIR := $(BASEDIR)/test

# Define the object's variables to be used later
OBJECTS :=
TEST_OBJECTS :=

# Since the paths to the files are long, they are all defined here
# Also the object's variables are updated
base.h := $(SRCDIR)/neuron/base.h
base.cpp := $(SRCDIR)/neuron/base.cpp
base.o := $(OBJDIR)/neuron/base.o
OBJECTS += $(base.o)

sigmoid.h = $(SRCDIR)/neuron/sigmoid.h
sigmoid.cpp = $(SRCDIR)/neuron/sigmoid.cpp
sigmoid.o = $(OBJDIR)/neuron/sigmoid.o
OBJECTS += $(sigmoid.o)

base_test.h := $(TESTDIR)/neuron/base_test.h
base_test.cpp := $(TESTDIR)/neuron/base_test.cpp
base_test.o := $(OBJDIR)/neuron/base_test.o
TEST_OBJECTS += $(base_test.o)

sigmoid_test.h := $(TESTDIR)/neuron/sigmoid_test.h
sigmoid_test.cpp := $(TESTDIR)/neuron/sigmoid_test.cpp
sigmoid_test.o := $(OBJDIR)/neuron/sigmoid_test.o
TEST_OBJECTS += $(sigmoid_test.o)

test.cpp := $(TESTDIR)/test.cpp
test.o := $(OBJDIR)/test.o
TEST_OBJECTS += $(test.o)

test.exe := $(BINDIR)/test

# List of phony targets
.PHONY: clean clean-all all test

# List of rules
all: $(OBJECTS) test

$(base.o): $(base.cpp) $(base.h) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(sigmoid.o) : $(sigmoid.cpp) $(sigmoid.h) $(base.o) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(test.exe)

$(test.exe): $(TEST_OBJECTS) $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest

$(base_test.o): $(base_test.cpp) $(base_test.h) $(base.h) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -Wno-unused-parameter -c $< -o $@

$(sigmoid_test.o): $(sigmoid_test.cpp) $(sigmoid_test.h) $(sigmoid.o) $(base.o) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(test.o): $(test.cpp) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -Wno-unused-parameter -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/neuron

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -Rf $(OBJDIR)

clean-all: clean
	rm -Rf $(BINDIR)
