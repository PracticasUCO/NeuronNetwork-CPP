#include "neuron.h"

namespace mp {
  template <class B>
  Neuron<B>::Neuron(const int &inputs_size, const bool bias_enabled) {
    resize(inputs_size);
    _bias_enabled = bias_enabled;
  }

  template <class B>
  void Neuron<B>::resize(const int &inputs_size){
    _factors.resize(inputs_size, 0.0);
    _factor_changes.resize(inputs_size, 0.0);
    _last_factor_changes.resize(inputs_size, 0.0);
  }

  template <class B>
  void Neuron<B>::set_factor(const int &index, const double &value){
    _last_factor_changes[index] = _factor_changes[index];
    _factor_changes[index] = _factors[index];
    _factors[index] = value;
  }

  template <class B>
  void Neuron<B>::set_factors(const vector<double> &factors){
    _last_factor_changes = _factor_changes;
    _factor_changes = _factors;
    _factors = factors;
  }

  template <class B>
  void Neuron<B>::set_bias(const double &value){
    _last_bias_change = _bias_change;
    _bias_change = _bias;
    _bias = value;
  }

  template <class B>
  void Neuron<B>::set_before_layer(vector<B> &layer) {
    _before_layer = layer;
  }

  template <class B>
  double Neuron<B>::output() const {
    return _output;
  }

  template <class B>
  double Neuron<B>::factor(const int &index) const{
    return _factors[index];
  }

  template <class B>
  double Neuron<B>::factor_change(const int &index) const{
    return _factor_changes[index];
  }

  template <class B>
  double Neuron<B>::last_factor_change(const int &index) const{
    return _last_factor_changes[index];
  }

  template <class B>
  bool Neuron<B>::bias_enabled() const {
    return _bias_enabled;
  }

  template <class B>
  double Neuron<B>::bias() const {
    if(bias_enabled()) return _bias;
    else return 0.0;
  }

  template <class B>
  double Neuron<B>::bias_change() const {
    if(bias_enabled()) return _bias_change;
    else return 0.0;
  }

  template <class B>
  double Neuron<B>::last_bias_change() const {
    if(bias_enabled()) return _last_bias_change;
    else return 0.0;
  }
}
