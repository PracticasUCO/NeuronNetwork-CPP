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
#include "data_test.h"

TEST_F(DataStructure, InputsLength) {
  ASSERT_EQ(2, dat.inputs_length());
}

TEST_F(DataStructure, OutputsLength) {
  ASSERT_EQ(1, dat.outputs_length());
}

TEST_F(DataStructure, Elements) {
  ASSERT_EQ(4, dat.elements());
}

TEST_F(DataStructure, Inputs) {
  vector<double> input0;
  vector<double> input1;
  vector<double> input2;
  vector<double> input3;

  input0.push_back(1);
  input0.push_back(-1);

  input1.push_back(-1);
  input1.push_back(-1);

  input2.push_back(-1);
  input2.push_back(1);

  input3.push_back(1);
  input3.push_back(1);

  ASSERT_TRUE( input_contain(dat, input0) ) << "[1, -1] is not included in data";
  ASSERT_TRUE( input_contain(dat, input1) ) << "[-1, -1] is not included in data";
  ASSERT_TRUE( input_contain(dat, input2) ) << "[-1, 1] is not included in data";
  ASSERT_TRUE( input_contain(dat, input3) ) << "[1, 1] is not included in data";
}

TEST_F(DataStructure, Outputs) {
  vector<double> input0;
  vector<double> input1;
  vector<double> input2;
  vector<double> input3;

  vector<double> output0;
  vector<double> output1;
  vector<double> output2;
  vector<double> output3;

  input0.push_back(1);
  input0.push_back(-1);
  output0.push_back(1);

  input1.push_back(-1);
  input1.push_back(-1);
  output1.push_back(0);

  input2.push_back(-1);
  input2.push_back(1);
  output2.push_back(1);

  input3.push_back(1);
  input3.push_back(1);
  output3.push_back(0);

  ASSERT_TRUE( output_contain(dat, input0, output0) ) << "[1, -1] must have a [1] as output";
  ASSERT_TRUE( output_contain(dat, input1, output1) ) << "[-1, -1] must have a [0] as output";
  ASSERT_TRUE( output_contain(dat, input2, output2) ) << "[-1, 1] must have a [1] as output";
  ASSERT_TRUE( output_contain(dat, input3, output3) ) << "[1, 1] must have a [0] as output";
}
