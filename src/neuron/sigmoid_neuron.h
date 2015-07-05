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
#ifndef ___SIGMOID__NEURON___
#define ___SIGMOID__NEURON___
#include <vector>
#include <memory>
#include <type_traits>
#include <cmath>
#include "base.h"

namespace MP { // Stands for Multilayer Perceptron
  namespace Neuron { // Neuron's namespace

    // Refresh implementation when T is an arithmetic type
    template <class T>
    typename std::enable_if<std::is_arithmetic<T>::value, double>::type
    refresh_impl(const std::shared_ptr<std::vector<T>> &before_layer, const std::vector<double> &factors, const double &bias) {
      double sum = bias;

      if(before_layer) {
        for(unsigned int i = 0; i < before_layer->size(); i++) {
          sum += factors.at(i) * before_layer->at(i);
        }
      }

      return 1/(1 + exp(-1 * sum));
    }

    // Refresh implementation when T is a pointer to a MP::Neuron::Base with a MP::Neuron::Base
    // specialization or a number specialization
    template <class T>
    typename std::enable_if<std::is_pointer<T>::value && 
    (std::is_base_of<MP::Neuron::Base<T>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<double>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<float>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<int>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<unsigned int>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<long int>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<long long int>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<unsigned long int>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<MP::Neuron::Base<unsigned long long int>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<double>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<float>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<int>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<long int>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<long long int>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<unsigned int>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<unsigned long int>>, typename std::remove_pointer<T>::type>::value ||
     std::is_base_of<std::shared_ptr<MP::Neuron::Base<unsigned long long int>>, typename std::remove_pointer<T>::type>::value), double>::type
    refresh_impl(const std::shared_ptr<std::vector<T>> &before_layer, const std::vector<double> &factors, const double &bias) {
      double sum = bias;

      if(before_layer) {
        for(unsigned int i = 0; i < before_layer->size(); i++) {
          sum += factors.at(i) * before_layer->at(i)->output();
        }
      }

      return 1/(1 + exp(-1 * sum));
    }

    template <typename T>
      class Sigmoid : public MP::Neuron::Base<T> {
        public:
          // Empty constructor
          Sigmoid() : MP::Neuron::Base<T>() {}

          // Fill constructor
          Sigmoid(const int &inputs_size, const bool &bias_enabled) :
          MP::Neuron::Base<T>(inputs_size, bias_enabled) {}

          // Fill constructor
          Sigmoid(const std::shared_ptr<std::vector<T>> &before_layer, const bool &bias_enabled) :
          MP::Neuron::Base<T>(before_layer, bias_enabled) {}

          // Fill constructor
          Sigmoid(const std::weak_ptr<std::vector<T>> &before_layer, const bool &bias_enabled) :
          MP::Neuron::Base<T>(before_layer, bias_enabled) {}

          // Copy constructor
          Sigmoid(const Base<T> &n) : MP::Neuron::Base<T>(n) {}

          // Destructor
          ~Sigmoid() {
          }

        protected:
          double refresh() override {
            return refresh_impl(this->before_layer().lock(), this->factors(), this->bias());
          }
      };
  }
}

#endif
