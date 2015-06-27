#include <gtest/gtest.h>
#include "neuron/sigmoid_neuron.h"

using namespace mp;

class SigmoidNeuronTest : public ::testing::Test {
  protected:
    SigmoidNeuronTest() { // Neuron setup here
    }

    virtual ~SigmoidNeuronTest() { //Clean up that doesn't throw exceptions here
    }

    virtual void SetUp() { //Code setup before each test
    }

    virtual void TearDown() { //Code called after each test
    }

    SigmoidNeuron<int> empty_neuron;
};
