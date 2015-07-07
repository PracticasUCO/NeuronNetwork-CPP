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
#include "sigmoid_test.h"

TEST_F(SigmoidWithInputLayer, CalculatesTheOutput) {
  EXPECT_NEAR(0.62245933120, neuron.output(), 1e-10);
}

TEST_F(SigmoidWithInputLayer, BiasAffectsTheOutput) {
  neuron.enable_bias();
  neuron.set_bias(2.5);
  neuron.refresh(input);
  EXPECT_NEAR(0.95257412682, neuron.output(), 1e-10);
}

TEST_F(SigmoidWithInputLayer, FactorsAffectsTheOutput) {
  neuron.set_factor(0, 0.5);
  neuron.set_factor(2, -0.5);
  neuron.refresh(input);
  EXPECT_NEAR(0.09534946489, neuron.output(), 1e-10);
}

TEST_F(SigmoidWithNeuronLayer, CalculatesTheOutput) {
  EXPECT_NEAR(0.77641901805, neuron.output(), 1e-10);
}

TEST_F(SigmoidWithNeuronLayer, BiasAffectsTheOutput) {
  neuron.enable_bias();
  neuron.set_bias(-1.75);
  neuron.refresh(neuron_layer);
  EXPECT_NEAR(0.37634728076, neuron.output(), 1e-10);
}

TEST_F(SigmoidWithNeuronLayer, FactorsAffectsTheOutput) {
  neuron.set_factor(0, 0.5);
  neuron.set_factor(1, -0.95);
  neuron.refresh(neuron_layer);
  EXPECT_NEAR(0.43042761756, neuron.output(), 1e-10);
}
