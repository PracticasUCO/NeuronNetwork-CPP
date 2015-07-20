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

TEST_F(GeneralNetwork, OutputsHaveAZeroLengthWhenSpreadOutIsNotCalled) {
  network net(3, 4, 5);
  vector<double> inputs;
  inputs.push_back(1);
  inputs.push_back(-1);

  ASSERT_EQ(0, net.output().size());

  net.feed(inputs);
  ASSERT_EQ(0, net.output().size());
}

TEST_F(GeneralNetwork, SpreadOutRefreshNetworkOutputs) {
  network net(1, 2, 1);
  vector<double> inputs;
  inputs.push_back(1);
  inputs.push_back(-1);

  for(unsigned int i = 0; i < net.layers(); i++) {
    for(unsigned int j = 0; j < net.layer_size( i ); j++) {
      auto neuron = net.neuron(i, j).lock();

      for(unsigned int h = 0; h < neuron->factors_size(); h++) {
        neuron->set_factor(h, 1);
      }
    }
  }

  net.feed(inputs);
  net.spread_out();
  ASSERT_EQ(1, net.output().size());
  ASSERT_NEAR(0.7310585786300049, net.output()[0], 1e-15);
}

TEST_F(GeneralNetwork, ApplySoftmaxMakesOutputSumsOne) {
  network net(10, 10, 20);
  vector<double> inputs;

  for(unsigned int i = 0; i < 15; i++) {
    if( i % 3 == 0 ) inputs.push_back(-i);
    else inputs.push_back(i);
  }

  net.feed(inputs);
  net.spread_out();
  net.apply_softmax();

  auto net_output = net.output();
  double sum = 0;

  for(double v : net_output) {
    sum += v;
  }

  ASSERT_NEAR(1, sum, 1e-15);
}

TEST_F(GeneralNetwork, BackpropagateSingleValue) {
  network net(3, 3, 1);
  vector<double> inputs;
  vector<double> expected;
  double start_error;
  double end_error;

  inputs.push_back(1);
  inputs.push_back(1);

  expected.push_back( 0.75 );

  net.feed( inputs );
  net.spread_out();

  start_error = abs(0.75 - net.output()[0]);

  for(unsigned int i = 0; i < 700; i++) {
    net.backpropagate( inputs, expected );
  }

  net.feed( inputs );
  net.spread_out();

  end_error = abs( 0.75 - net.output()[0] );

  EXPECT_LT( end_error, start_error );
}

TEST_F(GeneralNetwork, BackpropagateMultipleValues) {
  network net(3, 3, 1);
  vector<double> inputs0;
  vector<double> expected0;
  vector<double> inputs1;
  vector<double> expected1;
  double start_ex0;
  double start_ex1;
  double end_ex0;
  double end_ex1;
  double start_error;
  double end_error;

  for(unsigned int i = 0; i < net.layers(); i++) {
    for(unsigned int j = 0; j < net.layer_size( i ); j++) {
      auto n = net.neuron(i, j).lock();
      n->enable_bias();

      for(unsigned int f = 0; f < n->factors_size(); f++) {
        n->set_factor(f, 1);
      }
    }
  }

  inputs0.push_back( 1 );
  inputs0.push_back( 1 );
  expected0.push_back( 0 );

  inputs1.push_back( 1 );
  inputs1.push_back( -1 );
  expected1.push_back( 1 );

  net.feed(inputs0);
  net.spread_out();
  start_ex0 = net.output()[0];

  net.feed(inputs1);
  net.spread_out();
  start_ex1 = net.output()[0];

  start_error = sqrt(pow(-start_ex0, 2) + pow(1 - start_ex1, 2));

  for(unsigned int i = 0; i < 1400; i++) {
    net.backpropagate( inputs0, expected0 );
    net.backpropagate( inputs1, expected1 );
  }

  net.feed(inputs0);
  net.spread_out();
  end_ex0 = net.output()[0];

  net.feed(inputs1);
  net.spread_out();
  end_ex1 = net.output()[0];

  end_error = sqrt( pow( -end_ex0, 2) + pow(1 - end_ex1, 2) );

  EXPECT_LT( end_error, start_error );
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
