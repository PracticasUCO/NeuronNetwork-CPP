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
#include <memory>
#include "data.h"

using namespace mp;
using namespace std;

bool input_contain(const data &dat, const vector<double> &v) {
  bool result = false;

  for(unsigned int i = 0; i < dat.elements(); i++) {
    if( v == *(dat.input(i).lock()) ) {
      result = true;
      break;
    }
  }

  return result;
}

bool output_contain(const data &dat, const vector<double> &input, const vector<double> &output) {
  bool result = false;
  unsigned int index = -1;

  for(unsigned int i = 0; i < dat.elements(); i++) {
    if( input == *(dat.input(i).lock()) ) {
      result = true;
      index = i;
      break;
    }
  }

  if( result ) {
    result = *(dat.output( index ).lock()) == output;
  }

  return result;
}

class DataStructure : public ::testing::Test {
  protected:
    DataStructure() {
      dat.reload( "db/test_xor.dat" );
    }

    data dat;
};
