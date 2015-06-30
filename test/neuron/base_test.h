#include <gtest/gtest.h>
#include "neuron/base.h"

// Only with testing purposes
template <class T>
class FakeBase : public MP::Neuron::Base<T> {
  public:

  FakeBase() : MP::Neuron::Base<T>() {
  }

  FakeBase(const int &inputs_size, const bool &bias_enabled) : MP::Neuron::Base<T>(inputs_size, bias_enabled) {
  }

  inline double refresh() override {
    return 0.0;
  }
};

class EmptyBase : public ::testing::Test {
  protected:
    EmptyBase() {
    }

    ~EmptyBase() {
    }

    FakeBase<double> empty;
};

class ParametizerConstructor : public ::testing::Test {
  protected:
    ParametizerConstructor() {
    }

    ~ParametizerConstructor() {
    }

    FakeBase<double> neuron = FakeBase<double>(3, true);
};

class BaseMethods : public ::testing::Test {
  protected:
    BaseMethods() {
    }

    ~BaseMethods() {
    }

    FakeBase<double> empty;
    FakeBase<double> neuron = FakeBase<double>(3, true);
};
