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
#ifndef ___NETWORK___
#define ___NETWORK___
#include <vector>
#include <memory>
#include "neuron/base.h"
#include "neuron/sigmoid.h"

using namespace std;
using namespace mp::neuron;

namespace mp {
  /**
   * \class network network.h
   * \brief This class represents the multilayer percentron network.
   *
   * This class represents the multilayer perceptron network. It can handle networks
   * of different kind of neurons, but, by default it uses the sigmoid neuron.
   *
   * A Multilayer Perceptron Network, proyect a given inputs throw a few neuron's layers,
   * called hidden layers. At the end, the result is projected into a output layer and the
   * result of the network is collected.
   *
   * So the minimun number of layers that this kind of network can have is 2 (one
   * hidden layer and one output layer).
   *
   * By design, I tried that the network have a flexible structure, that implies:
   * - The length of each layer can be variable (Work In Progress)
   * - A layer can have any kind of neurons, with any kind of configuration, you can for
   *   example have a layer with three neurons, 2 of them sigmoid (one with bias, one without bias),
   *   and the another one RBF (with or without bias).
   * */
  class network {
    public:
      /**
       * It constructs a network with 1 hidden layer with one neuron, and one neuron in the
       * output layer.
       * */
      network();

      /**
       * It constructs a network with the specified length of hidden layers, each one with
       * the specified layer size, and the output layer with the specified output size
       * \param hidden_layers Number of hidden layers of the network
       * \param layer_size    Hidden layers size
       * \param output_size   Size of the output layer
       * */
      network(const unsigned int &hidden_layers, const unsigned int &layer_size,
              const unsigned int &output_size);

      /**
       * It feeds the neuron with the given inputs. Notice that the inputs don't need to have
       * a specified length. The network will be restructured to ensure that all layer are
       * correctly connected with the new inputs
       * */
      void feed(const vector<double> &inputs);

      /**
       * It updates the network map to have the specified number of hidden layers, each one with
       * the specified layer size, and the output layer with the specified output size
       * \param hidden_layers Number of hidden layers of the network
       * \param layer_size    Hidden layers size
       * \param output_size   Size of the output layer
       * */
      void update_network_map(const unsigned int &hidden_layers, const unsigned int &layer_size,
                              const unsigned int &output_size);

      /**
       * It stores the given neuron in the network. This can be useful to change the default
       * neurons.
       * \param layer_index  Layer where the neuron must be set
       * \param neuron_index Index of the neuron inside the layer
       * \param neuron       Smart pointer of the neuron that will be stored
       * */
      void neuron(const unsigned int &layer_index, const unsigned int &neuron_index,
                  const shared_ptr<base> &neuron);

      /**
       * It spread out the network neurons!
       * */
      void spread_out();

      /**
       * It applies a softmax function to the neuron outputs.
       * */
      void apply_softmax();

      /**
       * It tries to config the network to ensure that it get closer next time it tries to
       * get the given inputs,
       * \param inputs the inputs of the network
       * \param expected the expected result of the network
       * */
      void backpropagate(const vector<double> &inputs, const vector<double> &expected);

      /**
       * It returns the number of layers of the network (hidden layers + output layer).
       * \return the number of hidden layers of the network
       * */
      unsigned int layers() const;

      /**
       * It returns the size of the given layer. The layer_index is a number between 0 and
       * hidden_layers + 1 (or between 0 and layers() - 1 if you prefer)
       * \return the size of the specified layer
       * */
      unsigned int layer_size(const unsigned int &layer_index) const;

      /**
       * It returns a weak reference of the specified neuron.
       * \param layer_index  Layer where the neuron must be set
       * \param neuron_index Index of the neuron inside the layer
       * \return a weak pointer to the specified neuron
       * */
      weak_ptr<base> neuron(const unsigned int &layer_index,
                            const unsigned int &neuron_index) const;

      /**
       * It returns current network outputs
       * \return current network outputs
       * */
      vector<double> output() const;

      /**
       * It returns the network output when it is feeded with the given input
       * \param inputs the inputs for the network
       * \return the network outputs when it is feeded with the given inputs
       * */
      vector<double> output(const vector<double> &inputs);

    private:
      vector<double> _inputs;
      vector<vector<shared_ptr<base>>> _hidden_layers;
      vector<shared_ptr<base>> _output_layer;
      vector<double> _outputs;

      /**
       * It fix the neuron factors of the specified layer, and if the neuron is
       * not present, it creates it with the correct number of factors.
       * \param layer Index of the layer to fix
       * */
      void fix_layer_inputs(const unsigned int &layer);

      /**
       * It fix neuron factors in all layers. If it finds that a neuron is not present,
       * it will create a new sigmoid neuron with the right factors length and it will
       * set it.
       * */
      void fix_layer_inputs();

      /*
       * It retreives the layer specified at the given index
       * \param index the index of the layer to return
       * \return the specified layer
       * */
      const vector<shared_ptr<base>>& layer(const unsigned int &index) const;

      /**
       * It reset all neuron changes
       * */
      void reset_neuron_changes();

      /**
       * It update neuron's deltas
       * \param expected expected network's outputs
       * */
      void update_deltas(const vector<double> &expected);
      void update_output_deltas(const vector<double> &expected);
      void update_hidden_deltas();

      /**
       * It updates all neuron factors to improve the network output.
       * */
      void update_neuron_factors();

      /**
       * It adjust the neuron factors according to their deltas
       * */
      void adjust_weights();
  };
}
#endif
