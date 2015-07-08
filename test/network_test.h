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
#include <vector>
#include "network.h"

using namespace mp;
using namespace std;

class EmptyNetworkConstructor : public ::testing::Test {
  protected:
    EmptyNetworkConstructor() {}

    ~EmptyNetworkConstructor() {}

    network net;
};

class GeneralNetwork : public ::testing::Test {
  protected:
    GeneralNetwork() {}
    ~GeneralNetwork() {}
};

class ParametizerNetworkConstructor : public ::testing::Test {
  protected:
    ParametizerNetworkConstructor() {
      net = network(13, 8, 10);
    }

    ~ParametizerNetworkConstructor() {
    }

    network net;
};
