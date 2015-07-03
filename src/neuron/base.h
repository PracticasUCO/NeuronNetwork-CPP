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
#ifndef ___NEURON___
#define ___NEURON___
#include <vector>
#include <iostream>
#include <memory>

namespace MP { // Stands for MultilayerPerceptron
  namespace Neuron { //Neuron's namespace
    /**
     * \class Base neuron.h
     * \brief This class represents a neuron's base in the network. Each neuron have an arbitrary
     *  number of inputs, a bias (that can be active or not) and a delta.
     *
     * A neuron's base is a class that represent the basic unit of neuron network. Each neuron
     * receives an arbitrary number of inputs, process it, and return a value between 0 and 1.
     *
     * A neuron's base can have an array of doubles or an array of another neuros as inputs.
     * \note This class can not be instanciated You are enforced to use a derived class.
     * derived class must implement a method called refresh (used to propagate the outputs
     * throw the network).
     * */
    template <class B>
      class Base {
        public:

          /**
           * \brief It builds a neuron with bias disabled and zero inputs
           * **/
          inline Base() {
            disable_bias();
            _before_layer = nullptr;
            _bias = 0.0;
            _bias_change = 0.0;
            _last_bias_change = 0.0;
            _delta = 0.0;
            _refresh_output = false;
          }

          /**
           * \brief It initializes a neuron with the given inputs_size and with bias_enabled.
           * \param inputs_size the length of the given inputs
           * \param bias_enables indicates if the bias is enabled or not
           * */
          inline Base(const int &inputs_size, const bool &bias_enabled) {
            _bias_enabled = bias_enabled;
            _before_layer = nullptr;
            _bias = 0.0;
            _bias_change = 0.0;
            _last_bias_change = 0.0;
            _delta = 0.0;
            resize(inputs_size);
          }

          /**
           * \brief It initializes a neuron with the factors_size's length equal to the before_layer's
           * size, and bias enabled or disabled.
           * \param before_layer pointer to the before layer
           * \param bias_enabled indicates if the bias is enabled or not
           * */
          inline Base(const std::shared_ptr<std::vector<B>> &before_layer, const bool &bias_enabled) {
            _bias_enabled = bias_enabled;
            _before_layer = before_layer;
            _bias = 0.0;
            _bias_change = 0.0;
            _last_bias_change = 0.0;
            _delta = 0.0;

            if(before_layer) resize(before_layer->size());
            else resize(0);
          }

          /**
           * \brief It initializes a neuron with the factors_size's length equal to the before_layer's
           * size, and bias enabled or disabled.
           * \param before_layer pointer to the before layer
           * \param bias_enabled indicates if the bias is enabled or not
           * */
          inline Base(const std::weak_ptr<std::vector<B>> &before_layer, const bool &bias_enabled) :
                 Base(before_layer.lock(), bias_enabled) {
          }

          /**
           * \brief It creates a copy of the given neuron.
           * \param n the neuron to be copied
           * **/
          inline Base(const Base<B> &n) {
            set_delta( n.delta() );

            set_factors(n.last_factor_changes());
            set_factors(n.factor_changes());
            set_factors(n.factors());

            set_before_layer(std::shared_ptr<std::vector<B>>(n.before_layer()));

            if(n.bias_enabled()){
              enable_bias();
              _bias = n.bias();
              _bias_change = n.bias_change();
              _last_bias_change = n.last_bias_change();
            }
            else {
              _bias = 0.0;
              _bias_change = 0.0;
              _last_bias_change = 0.0;
              disable_bias();
            }
          }

          /**
           * \brief It resizes the neuron to have the factors_size length.
           * \param factors_size the size of the factors to this neuron
           * */
          inline void resize(const int &inputs_size) {
            _factors.resize(inputs_size, 0.0);
            _factor_changes.resize(inputs_size, 0.0);
            _last_factor_changes.resize(inputs_size, 0.0);
            set_output_refresh();
          }

          /**
           * \brief It sets a factor of the given neuron at the given index
           * \param index the position where the factor is set
           * \param value new factor's value
           * */
          inline void set_factor(const int &index, const double &value) {
            _last_factor_changes[index] = _factor_changes[index];
            _factor_changes[index] = _factors[index];
            _factors[index] = value;
            set_output_refresh();
          }

          /**
           * \brief It sets a new set of factors to the given neuron.
           * \param factors a vector with all new factors
           * */
          inline void set_factors(const std::vector<double> &factors) {
            _last_factor_changes = _factor_changes;
            _factor_changes = _factors;
            _factors = factors;
            set_output_refresh();
          }

          /**
           * \brief It enables the neuron bias if it is disabled
           * **/
          inline void enable_bias() {
            if(not bias_enabled()) _bias_enabled = true;
          }

          /**
           * \brief It disables the neuron bias if it is enabled
           * **/
          inline void disable_bias() {
            if(bias_enabled()) _bias_enabled = false;
          }

          /**
           * \brief It sets a new bias value
           * \param value the new bias value
           * */
          inline void set_bias(const double &value) {
            _last_bias_change = _bias_change;
            _bias_change = _bias;
            _bias = value;
            set_output_refresh();
          }

          /**
           * \brief It sets a pointer to the layer that is before this neuron. The
           * layer will influence this neuron in its outputs.
           * Notice that the factor's size will be set accordingly with the size
           * of the layer that is set.
           * \param layer the layer that is before this neuron.
           * */
          inline void set_before_layer(const std::shared_ptr<std::vector<B>> &layer) {
            _before_layer = layer;
            resize(layer->size());
            set_output_refresh();
          }

          /**
           * \brief It sets how much the neuron will try to fix its own errors.
           * \param delta a value between 0 and 1 that specify how much the neuron will try to fix its
           * own errors (0 it will not try, 1 it will do it completly)
           * **/
          inline void set_delta(const double &delta) {
            _delta = delta;
          }

          /**
           * \brief It returns the neuron output. It refresh the output if needed.
           * \return the output of this neuron.
           * */
          inline double output() {
            if(need_refresh()) refresh();
            return _output;
          }

          /**
           * \brief It returns the specified factor applied to the neuron's input
           * \param index index of the neuron's factor
           * \return the neuron's factor specified at the given index.
           * */
          inline double factor(const int &index) const {
            return _factors[index];
          }

          /**
           * \brief It returns the factor change applied to the neuron's input
           * \param index index of the neuron's factor
           * \return the change made to the neuron's factor
           * */
          inline double factor_change(const int &index) const {
            return _factor_changes[index];
          }

          /**
           * \brief It returns the last factor change applied to the neuron's input
           * \param index index of the neuron's factor
           * \return the last change made to the neuron's factor
           * */
          inline double last_factor_change(const int &index) const {
            return _last_factor_changes[index];
          }

          /**
           * \brief It returns the number of factors in the neuron
           * \return the factor's size
           * **/
          inline int factors_size() const {
            return _factors.size();
          }

          /**
           * \brief It returns the list of factors of this neuron
           * \return a vector with all of the factors of this neuron.
           * **/
          inline const std::vector<double>& factors() const {
            return _factors;
          }

          /**
           * \brief It returns the list of factor changes in this neuron.
           * \return a vector with all factor changes on this neuron.
           * **/
          inline const std::vector<double>& factor_changes() const {
            return _factor_changes;
          }

          /**
           * \brief It returns the list of last factor changes in this neuron.
           * \return a vector with all last factor changes on this neuron.
           * **/
          inline const std::vector<double>& last_factor_changes() const {
            return _last_factor_changes;
          }

          /**
           * \brief It checks if the neuron have a bias enabled.
           * \return a true value if the bias is enabled, false otherwise
           * */
          inline bool bias_enabled() const {
            return _bias_enabled;
          }

          /**
           * \brief It returns the bias value if it is enabled, zero otherwise.
           * \return the bias value if it is enabled, zero otherwise.
           * */
          inline double bias() const {
            if(bias_enabled()) return _bias;
            else return 0.0;
          }

          /**
           * \brief It returns the bias change if bias is enabled, zero otherwise.
           * \return the bias change if it is enabled, zero otherwise.
           * */
          inline double bias_change() const {
            if(bias_enabled()) return _bias_change;
            else return 0.0;
          }

          /**
           * \brief It returns the last bias change if bias is enabled, zero otherwise.
           * \return the last bias change if bias is enabled, zero otherwise.
           * */
          inline double last_bias_change() const {
            if(bias_enabled()) return _last_bias_change;
            else return 0.0;
          }

          /**
           * \brief It returns the neuron's delta
           * \return The neuron's delta
           * **/
          inline double delta() const {
            return _delta;
          }

          /**
           * \brief It returns the before layer of this neuron
           * \return the before layer of this neuron.
           * **/
          inline std::weak_ptr<std::vector<B>> before_layer() const {
            return std::weak_ptr<std::vector<B>>(_before_layer);
          }

        protected:
          /**
           * \brief It refresh the neuron output if needed
           * \return the new output value after refresh it.
           * */
          virtual double refresh() =0;

          /**
           * \brief It sets the refresh output flag to true.
           * */
          inline void set_output_refresh() {
            _refresh_output = true;
          }

          /**
           * \brief It sets the refresh output flag to false.
           * */
          inline void unset_output_refresh() {
            _refresh_output = false;
          }

          inline ~Base() {
          }

        private:
          std::shared_ptr<std::vector<B>> _before_layer;
          std::vector<double> _factors;
          std::vector<double> _factor_changes;
          std::vector<double> _last_factor_changes;
          double _bias;
          double _bias_change;
          double _last_bias_change;
          bool _bias_enabled;
          double _delta;
          double _output;
          bool _refresh_output;

          /**
           * \brief It checks if the output needs a refresh.
           * \return true if the neuron must call to refresh to update the output, false otherwise
           * */
          inline bool need_refresh() {
            return _refresh_output;
          }

      }; // Base Class

  } // namespace neuron

} // namespace mp
#endif
