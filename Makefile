# General settings
CC := clang++
CFLAGS := -std=c++14 -Wall -pedantic -ggdb3

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
neuron.h := $(SRCDIR)/neuron/neuron.h
neuron.cpp := $(SRCDIR)/neuron/neuron.cpp
neuron.o := $(OBJDIR)/neuron/neuron.o
OBJECTS += $(neuron.o)

sigmoid_neuron_test.h := $(TESTDIR)/neuron/sigmoid_neuron_test.h
sigmoid_neuron_test.cpp := $(TESTDIR)/neuron/sigmoid_neuron_test.cpp
sigmoid_neuron_test.o := $(OBJDIR)/neuron/sigmoid_neuron.o
TEST_OBJECTS += $(sigmoid_neuron_test.o)

test.cpp := $(TESTDIR)/test.cpp
test.o := $(OBJDIR)/test.o
TEST_OBJECTS += $(test.o)

test.exe := $(BINDIR)/test

# List of phony targets
.PHONY: clean clean-all all

# List of rules
all: $(OBJECTS) $(test.exe)

$(test.exe): $(TEST_OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ -lgtest

$(neuron.o): $(neuron.cpp) $(neuron.h) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(sigmoid_neuron_test.o): $(sigmoid_neuron_test.cpp) $(sigmoid_neuron_test.h) $(sigmoid_neuron.o) $(neuron.o) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(test.o): $(test.cpp) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/neuron

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -Rf $(OBJDIR)

clean-all: clean
	rm -Rf $(BINDIR)
