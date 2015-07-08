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
#include "network.h"

namespace mp {
  network::network() {
    update_network_map(1, 1, 1);
  }


  network::network(const unsigned int &hidden_layers, const unsigned int &layer_size,
                   const unsigned int &output_size) {
    update_network_map(hidden_layers, layer_size, output_size);
  }

  void network::feed(const vector<double> &inputs) {
    unsigned int old_inputs_size = _inputs.size();
    _inputs = inputs;
    if( old_inputs_size != inputs.size() ) fix_layer_inputs( 0 );
  }

  void network::update_network_map(const unsigned int &hidden_layers,
                                   const unsigned int &layer_size,
                                   const unsigned int &output_size) {
    _hidden_layers.resize( hidden_layers );
    _output_layer.resize( output_size );

    for(unsigned int i = 0; i < hidden_layers; i++) {
      auto layer = _hidden_layers.at( i );
      layer.resize( layer_size );
      _hidden_layers[i] = layer;
    }
    fix_layer_inputs();
  }

  void network::neuron(const unsigned int &layer_index, const unsigned int &neuron_index,
                       const shared_ptr<base> &neuron) {
    if( layer_index == layers() - 1 ) {
      _output_layer[neuron_index] = neuron;
    } else {
      auto layer = _hidden_layers.at( layer_index );
      layer[neuron_index] = neuron;
      _hidden_layers[layer_index] = layer;
    }
  }

  unsigned int network::layers() const {
    return _hidden_layers.size() + 1;
  }

  unsigned int network::layer_size(const unsigned int &layer_index) const {
    if( layer_index == layers() - 1 ) return _output_layer.size();
    else return _hidden_layers.at( layer_index ).size();
  }

  weak_ptr<base> network::neuron(const unsigned int &layer_index,
                                 const unsigned int &neuron_index) const {
    if( layer_index == layers() - 1 ) return weak_ptr<base>( _output_layer.at( neuron_index ) );
    else return weak_ptr<base>( _hidden_layers.at( layer_index ).at( neuron_index ) );
  }

  void network::fix_layer_inputs(const unsigned int &layer) {
    if( layer == 0 ) {
      auto before_size = _inputs.size();

      for(unsigned int i = 0; i < layer_size( layer ); i++) {
        auto n = neuron( layer, i ).lock();
        if(( n ) && ( n->factors_size() != before_size )) n->resize( before_size );
        else if( not n ) neuron(layer, i, shared_ptr<base>(new sigmoid( before_size, false )));
      }
    } else {
      auto before_size = layer_size( layer - 1 );

      for(unsigned int i = 0; i < layer_size( layer ); i++) {
        auto n = neuron( layer, i ).lock();
        if(( n ) && ( n->factors_size() != before_size ) ) n->resize( before_size );
        else if( not n ) neuron( layer, i, shared_ptr<base>( new sigmoid( before_size, false ) ) );
      }
    }
  }

  void network::fix_layer_inputs() {
    for(unsigned int i = 0; i < layers(); i++) {
      fix_layer_inputs( i );
    }
  }
}
