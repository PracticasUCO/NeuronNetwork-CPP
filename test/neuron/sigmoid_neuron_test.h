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
#include <vector>
#include <memory>
#include "neuron/sigmoid_neuron.h"

class SigmoidWithInputLayer : public ::testing::Test {
  protected:
    SigmoidWithInputLayer() {
      input = std::shared_ptr<std::vector<double>>(new std::vector<double>);

      for(unsigned int i = 0; i < 3; i++) {
        input->push_back(i + 1);
      }

      (*input)[1] *= -1;
      (*input)[2] /= 2;
      //input = [1, -2, 1.5]

      neuron = MP::Neuron::Sigmoid<double>(input, false);
      for(unsigned int i = 0; i < neuron.factors_size(); i++) {
        neuron.set_factor(i, 1);
      }
    }

    ~SigmoidWithInputLayer() {}

    MP::Neuron::Sigmoid<double> neuron;
    std::shared_ptr<std::vector<double>> input;
};


class SigmoidWithNeuronLayer : public ::testing::Test {
  protected:
    SigmoidWithNeuronLayer() {
      input = std::shared_ptr<std::vector<double>>( new std::vector<double> );
      neuron_layer = std::shared_ptr<std::vector<MP::Neuron::Base<double> *>>( new std::vector<MP::Neuron::Base<double> *> );

      input->push_back(1);
      input->push_back(-2);
      input->push_back(1.5);

      neuron_layer->push_back(new MP::Neuron::Sigmoid<double>(input, false));
      neuron_layer->push_back(new MP::Neuron::Sigmoid<double>(input, false));
      neuron = MP::Neuron::Sigmoid<MP::Neuron::Base<double> *>(neuron_layer, false);

      for(unsigned int i = 0; i < neuron_layer->size(); i++) {
        for(unsigned int j = 0; j < neuron_layer->at(i)->factors_size(); j++) {
          neuron_layer->at(i)->set_factor(j, 1);
        }
      }

      neuron.set_factor(0, 1);
      neuron.set_factor(1, 1);
    }

    ~SigmoidWithNeuronLayer() {}

    std::shared_ptr<std::vector<double>> input;
    std::shared_ptr<std::vector<MP::Neuron::Base<double> *>> neuron_layer;
    MP::Neuron::Sigmoid<MP::Neuron::Base<double> *> neuron;
};
