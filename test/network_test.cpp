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
#include "network_test.h"

TEST_F(EmptyNetworkConstructor, HaveTwoLayers) {
  EXPECT_EQ(2, net.layers());
}

TEST_F(EmptyNetworkConstructor, EachLayerHaveOneNeuron) {
  for(unsigned int i = 0; i < net.layers(); i++) {
    ASSERT_EQ(1, net.layer_size( i ));

    for(unsigned int j = 0; j < net.layer_size( i ); j++) {
      ASSERT_FALSE(net.neuron(i, j).expired());
    }
  }
}

TEST_F(GeneralNetwork, NeuronsAreDestroyedWithTheNetwork) {
  vector<weak_ptr<mp::neuron::base>> neuron_ptrs;

  {
    network net(9, 3, 4);
    for(unsigned int i = 0; i < net.layers(); i++) {
      for(unsigned int j = 0; j < net.layer_size( i ); j++) {
        neuron_ptrs.push_back( net.neuron(i, j) );
      }
    }
  }

  for( auto neuron_ptr : neuron_ptrs ) {
    ASSERT_TRUE( neuron_ptr.expired() );
  }
}

TEST_F(GeneralNetwork, NeuronsAreUnique) {
  network net(10, 9, 5);

  for(unsigned int i = 0; i < net.layers(); i++) {
    for(unsigned int j = 0; j < net.layer_size( i ); j++) {
      ASSERT_EQ(2, net.neuron(i, j).lock().use_count());
    }
  }
}

TEST_F(GeneralNetwork, FistHiddenLayerNeuronsHaveZeroFactorsLength) {
  network net(10, 9, 5);
  for(unsigned int i = 0; i < net.layer_size( 0 ); i++) {
    ASSERT_EQ(0, net.neuron(0, i).lock()->factors_size());
  }
}

TEST_F(GeneralNetwork, HiddenLayersNeuronsHaveBeforeLayerSize) {
  network net(10, 9, 5);

  for(unsigned int i = 1; i < net.layers() - 1; i++) {
    for(unsigned int j = 0; j < net.layer_size( i ); j++) {
      ASSERT_EQ(net.layer_size(i - 1), net.neuron(i, j).lock()->factors_size());
    }
  }
}

TEST_F(GeneralNetwork, FeedTheNetworkWillUpdateFistLayerFactors) {
  network net(3, 4, 5);
  vector<double> inputs;
  inputs.push_back(1);
  inputs.push_back(2);

  net.feed(inputs);

  for(unsigned int i = 0; i < net.layer_size( 0 ); i++) {
    ASSERT_EQ(2, net.neuron(0, i).lock()->factors_size());
  }

  net.feed(inputs);

  for(unsigned int i = 0; i < net.layer_size( 0 ); i++) {
    ASSERT_EQ(2, net.neuron(0, i).lock()->factors_size());
  }

  inputs.push_back(19);
  net.feed(inputs);

  for(unsigned int i = 0; i < net.layer_size( 0 ); i++) {
    ASSERT_EQ(3, net.neuron(0, i).lock()->factors_size());
  }

  inputs.clear();
  inputs.push_back(1);
  net.feed(inputs);

  for(unsigned int i = 0; i < net.layer_size( 0 ); i++) {
    ASSERT_EQ(1, net.neuron(0, i).lock()->factors_size());
  }
}

TEST_F(GeneralNetwork, FeedTheNetworkWillNotAffectSecondAndNextLayers) {
  network net(3, 4, 5);
  vector<double> inputs;
  inputs.push_back(1);
  inputs.push_back(2);

  net.feed(inputs);

  for(unsigned int i = 0; i < net.layers() - 1; i++) {
    ASSERT_EQ(4, net.layer_size(i));
  }

  ASSERT_EQ(5, net.layer_size( net.layers() - 1 ));

  for(unsigned int i = 1; i < net.layers(); i++) {
    for(unsigned int j = 0; j < net.layer_size( i ); j++ ) {
      ASSERT_EQ(net.layer_size(i - 1), net.neuron(i, j).lock()->factors_size());
    }
  }
}

TEST_F(ParametizerNetworkConstructor, MustHaveTheSpecifiedNumberOfLayersPlusOne) {
  EXPECT_EQ(14, net.layers());
}

TEST_F(ParametizerNetworkConstructor, HiddenLayersHaveTheSpecifiedLength) {
  for(unsigned int i = 0; i < net.layers() - 2; i++) {
    ASSERT_EQ(8, net.layer_size( i ));
  }
}

TEST_F(ParametizerNetworkConstructor, OutputLayerHaveTheSpecifiedLength) {
  EXPECT_EQ(10, net.layer_size( net.layers() - 1 ));
}
