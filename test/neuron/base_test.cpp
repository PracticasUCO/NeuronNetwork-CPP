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
#include "base_test.h"

/*
 * A Base neuron created with the empty constructor must:
 * - Have a factor's length of zero
 * - Have bias disabled
 * - Have before layer to nullptr
 * */
TEST_F(EmptyBase, FactorsAreEmpty) {
  EXPECT_EQ(0, empty.factors_size()) << "A empty neuron start with a zero factor's length";
  EXPECT_FALSE(empty.bias_enabled()) << "Bias must be disabled in a empty neuron";
}

/*
 * A Base neuron created with Base(3, true) must:
 * - Have a factor's length of 3
 * - Have bias enabled
 * - Have before layer to nullptr
 * */
TEST_F(ParametizerConstructor, ParametersSet) {
  EXPECT_EQ(3, neuron.factors_size()) << "The neuron shall be constructed with a three factor's length";
  EXPECT_TRUE(neuron.bias_enabled()) << "Bias must be enabled";
}

/*
 * Resize method must:
 * - Resize the factor's length
 * - Factors must be set to zero
 * - All factors must be resized
 * */
TEST_F(BaseMethods, ResizeMethod) {
  for(int i = 0; i < 25; i++) {
    neuron.resize(i);
    ASSERT_EQ(i, neuron.factors_size()) << "Neuron's factors shall be resize to " << i;

    for(unsigned int j = 0; j < neuron.factors_size(); j++) {
      EXPECT_EQ(0, neuron.factor(j)) << "After a resize, neuron's factors must be zero.";
      EXPECT_EQ(0, neuron.factor_change(j)) << "After a reize, neuron's factors must be zero.";
      EXPECT_EQ(0, neuron.last_factor_change(j)) << "After a resize, neuron's factors must be zero";
    }
  }
}

/*
 * Set Factor method must:
 * - Set the specified factor.
 * - Update factor change and last factor change
 * */
TEST_F(BaseMethods, SetFactorMethod) {
  neuron.set_factor(0, 3);
  neuron.set_factor(0, 2);
  neuron.set_factor(0, 1);

  EXPECT_EQ(1, neuron.factor(0)) << "The neuron must set the new factor value.";
  EXPECT_EQ(2, neuron.factor_change(0)) << "The neuron must remember factor's changes.";
  EXPECT_EQ(3, neuron.last_factor_change(0)) << "The neuron must remember factor's changes.";
}

/*
 * Set Factors method must
 * - Update all factors
 * - Update factors change and last factors change
 * */
TEST_F(BaseMethods, SetFactorsMethod) {
  std::vector<double> factor;
  std::vector<double> factor_change;
  std::vector<double> last_factor_change;

  for(int i = 0; i < 3; i++) {
    factor.push_back(1);
    factor_change.push_back(2);
    last_factor_change.push_back(3);
  }

  neuron.set_factors(last_factor_change);
  neuron.set_factors(factor_change);
  neuron.set_factors(factor);

  for(int i = 0; i < 3; i++) {
    EXPECT_EQ(1, neuron.factor(i)) << "Neuron's factors shall be updated";
    EXPECT_EQ(2, neuron.factor_change(i)) << "A neuron shall remember the factor's changes.";
    EXPECT_EQ(3, neuron.last_factor_change(i)) << "A neuron shall remember the factor's changes.";
  }
}

/*
 * Enable bias must set bias to true
 * */
TEST_F(BaseMethods, EnableBias) {
  empty.enable_bias();
  empty.set_bias(12.25);

  ASSERT_TRUE(empty.bias_enabled()) << "Bias shall be enabled";
  ASSERT_EQ(12.25, empty.bias()) << "The bias value shall be 12.25";
}

/*
 * Disable bias must set bias to false
 * */
TEST_F(BaseMethods, DisableBias) {
  neuron.set_bias(5);
  neuron.disable_bias();

  ASSERT_FALSE(neuron.bias_enabled()) << "Bias shall be disabled";
  ASSERT_EQ(0, neuron.bias()) << "The bias value shall be 0";
}

/*
 * Set delta must set new delta value
 * */
TEST_F(BaseMethods, SetDelta) {
  for(double i = 0; i < 1; i += 0.001) {
    empty.set_delta(i);

    ASSERT_EQ(i, empty.delta()) << "Delta value shall be updated to " << i;
  }
}

/**
 * Factors must return the array of factors
 * */
TEST_F(BaseMethods, Factors) {
  std::vector<double> factors = neuron.factors();

  ASSERT_EQ(factors.size(), neuron.factors_size());
}
