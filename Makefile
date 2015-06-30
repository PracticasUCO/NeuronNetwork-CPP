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
base.h := $(SRCDIR)/neuron/base.h

base_test.h := $(TESTDIR)/neuron/base_test.h
base_test.cpp := $(TESTDIR)/neuron/base_test.cpp
base_test.o := $(OBJDIR)/neuron/base_test.o
TEST_OBJECTS += $(base_test.o)

test.cpp := $(TESTDIR)/test.cpp
test.o := $(OBJDIR)/test.o
TEST_OBJECTS += $(test.o)

test.exe := $(BINDIR)/test

# List of phony targets
.PHONY: clean clean-all all test

# List of rules
all: $(OBJECTS) test

test: $(test.exe)

$(test.exe): $(TEST_OBJECTS) $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ -lgtest

$(base_test.o): $(base_test.cpp) $(base_test.h) $(base.h) | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

$(test.o): $(test.cpp) | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/neuron

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -Rf $(OBJDIR)

clean-all: clean
	rm -Rf $(BINDIR)
