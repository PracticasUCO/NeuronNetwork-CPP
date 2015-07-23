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

  void network::spread_out() {
    for(unsigned int i = 0; i < layers(); i++) {
      for(unsigned int j = 0; j < layer_size( i ); j++) {
        if( i == 0 ) neuron(i, j).lock()->refresh( _inputs );
        else neuron(i, j).lock()->refresh( layer( i - 1 ) );
      }
    }

    _outputs.clear();
    _outputs.reserve( _output_layer.size() );

    for( auto neuron : _output_layer ) {
      _outputs.push_back( neuron->output() );
    }
  }

  void network::apply_softmax() {
    double sum = 0;
    for(unsigned int i = 0; i < _outputs.size(); i++){
      sum += _outputs.at( i );
    }

    for(unsigned int i = 0; i < _outputs.size(); i++) {
      _outputs[i] /= sum;
    }
  }

  void network::backpropagate(const vector<double> &inputs, const vector<double> &expected) {
    feed(inputs);
    spread_out();
    reset_neuron_changes();
    update_deltas(expected);
    update_neuron_factors();
    adjust_weights();
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

  vector<double> network::output() const {
    return _outputs;
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

  vector<double> network::output(const vector<double> &inputs) {
    feed( inputs );
    spread_out();
    return _outputs;
  }

  void network::fix_layer_inputs() {
    for(unsigned int i = 0; i < layers(); i++) {
      fix_layer_inputs( i );
    }
  }

  const vector<shared_ptr<base>>& network::layer(const unsigned int &index) const {
    if( index == layers() - 1 ) return _output_layer;
    else return _hidden_layers.at( index );
  }

  void network::reset_neuron_changes() {
    for(unsigned int i = 0; i < layers(); i++) {
      for(unsigned int j = 0; j < layer_size( i ); j++) {
        neuron(i, j).lock()->reset_changes();
      }
    }
  }

  void network::update_deltas(const vector<double> &expected) {
    update_output_deltas(expected);
    update_hidden_deltas();
  }

  void network::update_output_deltas(const vector<double> &expected) {
    for(unsigned int i = 0; ((i < expected.size()) || (i < _output_layer.size())); i++) {
      auto neuron = _output_layer.at( i );

      double delta_value = -( expected.at(i) - neuron->output() ) * neuron->output();
      delta_value *= (1 - neuron->output());

      neuron->set_delta( delta_value );
    }
  }

  void network::update_hidden_deltas() {
    for(unsigned int h = layers() - 2; h < layers() - 1; h--) {
      for(unsigned int n = 0; n < layer_size( h ); n++) {
        auto hide_neuron = neuron(h, n).lock();
        double delta = 0;

        for(unsigned int i = 0; i < layer_size( h + 1 ); i++) {
          auto next = neuron(h + 1, i).lock();
          delta += (next->delta() * next->factor(i));
        }

        delta *= hide_neuron->output() * (1 - hide_neuron->output());
        hide_neuron->set_delta(delta);
      }
    }
  }

  void network::update_neuron_factors() {
    for(unsigned int i = 0; i < layers(); i++) {
      for(unsigned int j = 0; j < layer_size( i ); j++) {
        auto hide_neuron = neuron(i, j).lock();

        for(unsigned int f = 0; f < hide_neuron->factors_size(); f++) {
          if( i == 0 ) { // Between input and first hidden layer
            hide_neuron->add_factor_change(f, hide_neuron->delta() * _inputs.at(f));
          } else { // Between hidden layers
            auto before_neuron = neuron( i - 1, j ).lock();
            hide_neuron->add_factor_change(f, hide_neuron->delta() * before_neuron->output());
          }
        }
      }
    }
  }

  void network::adjust_weights() {
    for(unsigned int i = 0; i < layers(); i++) {
      for(unsigned int j = 0; j < layer_size( i ); j++) {
        auto hide_neuron = neuron(i, j).lock();
        hide_neuron->apply_changes(0.9, 0.1);
      }
    }
  }
}
