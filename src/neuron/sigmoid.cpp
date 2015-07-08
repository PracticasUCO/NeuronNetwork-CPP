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
#include "sigmoid.h"

namespace mp {
  namespace neuron {
    sigmoid::sigmoid() : mp::neuron::base() {}

    sigmoid::sigmoid(const unsigned int &inputs_size, const bool &bias_enabled) :
    mp::neuron::base(inputs_size, bias_enabled) {}

    sigmoid::sigmoid(const base &n) : mp::neuron::base(n) {}

    double sigmoid::calculate_output(const std::vector<double> &input_layer) {
      double sum = this->bias();

      for(unsigned int i = 0; ((i < input_layer.size()) || (i < this->factors_size())); i++) {
        sum += (input_layer.at(i) * this->factor(i));
      }

      return 1/(1 + exp(-1 * sum));
    }

    double sigmoid::calculate_output(const std::vector<base *> &neuron_layer) {
      double sum = this->bias();

      for(unsigned int i = 0; ((i < neuron_layer.size()) || (i < this->factors_size())); i++) {
        sum += (neuron_layer.at(i)->output() * this->factor(i));
      }

      return 1/(1 + exp(-1 * sum));
    }

    sigmoid::~sigmoid() {
    }
  }
}
