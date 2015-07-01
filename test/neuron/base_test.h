//
//    NeuronNetwork-CPP
//    Copyright (C) 2015  Pedro José Piquero Plaza <gowikel@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
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
