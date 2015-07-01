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

  FakeBase() :
  MP::Neuron::Base<T>() {}

  FakeBase(const int &inputs_size, const bool &bias_enabled) :
  MP::Neuron::Base<T>(inputs_size, bias_enabled) {}

  FakeBase(const std::shared_ptr<std::vector<T>> &before_layer, const bool &bias) :
  MP::Neuron::Base<T>(before_layer, bias) {}

  FakeBase(const std::weak_ptr<std::vector<T>> &before_layer, const bool &bias) :
  MP::Neuron::Base<T>(before_layer, bias) {}

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

class LayerConstructor : public ::testing::Test {
  protected:
    LayerConstructor() {
      before_layer_pointer = std::shared_ptr<std::vector<double>>(new std::vector<double>);

      for(int i = 0; i < 5; i++) {
        before_layer_pointer->push_back(i);
      }

      shared_neuron = FakeBase<double>(before_layer_pointer, true);
      weak_neuron = FakeBase<double>(std::weak_ptr<std::vector<double>>(before_layer_pointer), true);

      shared_neuron_no_bias = FakeBase<double>(before_layer_pointer, false);
      weak_neuron_no_bias = FakeBase<double>(std::weak_ptr<std::vector<double>>(before_layer_pointer), false);

      for(unsigned int i = 0; i < before_layer_pointer->size(); i++) {
        (*before_layer_pointer)[i] = (*before_layer_pointer)[i] * 2.5;
      }
    }
    ~LayerConstructor() {}

    FakeBase<double> shared_neuron;
    FakeBase<double> weak_neuron;

    FakeBase<double> shared_neuron_no_bias;
    FakeBase<double> weak_neuron_no_bias;

    std::shared_ptr<std::vector<double>> before_layer_pointer;
};

class NullLayerConstructor : public ::testing::Test {
  protected:
  NullLayerConstructor() {
    before_layer_pointer = nullptr;
    neuron = FakeBase<double>(before_layer_pointer, true);
    neuron_no_bias = FakeBase<double>(before_layer_pointer, false);
    neuron_nullptr = FakeBase<double>(nullptr, true);
    neuron_nullptr_no_bias = FakeBase<double>(nullptr, false);
  }

  ~NullLayerConstructor() {
  }

  FakeBase<double> neuron;
  FakeBase<double> neuron_no_bias;
  FakeBase<double> neuron_nullptr;
  FakeBase<double> neuron_nullptr_no_bias;
  std::shared_ptr<std::vector<double>> before_layer_pointer;
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
