//
//    NeuronNetwork-CPP
//    Copyright (C) 2015  Pedro José Piquero Plaza <gowikel@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <gtest/gtest.h>
#include <vector>
#include "neuron/sigmoid.h"

class SigmoidWithInputLayer : public ::testing::Test {
  protected:
    SigmoidWithInputLayer() {
      for(unsigned int i = 0; i < 3; i++) {
        input.push_back(i + 1);
      }

      input[1] *= -1;
      input[2] /= 2;
      //input = [1, -2, 1.5]

      neuron = mp::neuron::sigmoid(input.size(), false);
      for(unsigned int i = 0; i < neuron.factors_size(); i++) {
        neuron.set_factor(i, 1);
      }
      neuron.refresh(input);
    }

    ~SigmoidWithInputLayer() {}

    mp::neuron::sigmoid neuron;
    std::vector<double> input;
};


class SigmoidWithNeuronLayer : public ::testing::Test {
  protected:
    SigmoidWithNeuronLayer() {
      input.push_back(1);
      input.push_back(-2);
      input.push_back(1.5);

      neuron_layer.push_back(std::shared_ptr<mp::neuron::base>(new mp::neuron::sigmoid(input.size(), false)));
      neuron_layer.push_back(std::shared_ptr<mp::neuron::base>(new mp::neuron::sigmoid(input.size(), false)));
      neuron = mp::neuron::sigmoid(neuron_layer.size(), false);

      for(auto hide_neuron : neuron_layer) {
        for(unsigned int j = 0; j < hide_neuron->factors_size(); j++) {
          hide_neuron->set_factor(j, 1);
        }
      }

      neuron.set_factor(0, 1);
      neuron.set_factor(1, 1);

      for(auto hide_neuron : neuron_layer) {
        hide_neuron->refresh(input);
      }

      neuron.refresh(neuron_layer);
    }

    ~SigmoidWithNeuronLayer() {}

    std::vector<double> input;
    std::vector<std::shared_ptr<mp::neuron::base>> neuron_layer;
    mp::neuron::sigmoid neuron;
};
