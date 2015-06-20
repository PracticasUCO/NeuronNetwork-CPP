#include "neuron.h"

namespace mp {
  template <class B>
  Neuron<B>::Neuron(){
    disable_bias();
    _before_layer = nullptr;
    _bias = 0.0;
    _bias_change = 0.0;
    _last_bias_change = 0.0;
    _delta = 0.0;
    _refresh_output = false;
  }

  template <class B>
  Neuron<B>::Neuron(const int &inputs_size, const bool bias_enabled) {
    _bias_enabled = bias_enabled;
    _before_layer = nullptr;
    _bias = 0.0;
    _bias_change = 0.0;
    _last_bias_change = 0.0;
    _delta = 0.0;
    resize(inputs_size);
  }

  template <class B>
  Neuron<B>::Neuron(const Neuron<B> &n) {
    set_delta( n.delta );

    set_factors(n.last_factor_changes());
    set_factors(n.factor_changes());
    set_factors(n.factors());

    set_before_layer(n.before_layer());

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

  template <class B>
  void Neuron<B>::resize(const int &inputs_size){
    _factors.resize(inputs_size, 0.0);
    _factor_changes.resize(inputs_size, 0.0);
    _last_factor_changes.resize(inputs_size, 0.0);
    set_output_refresh();
  }

  template <class B>
  void Neuron<B>::set_factor(const int &index, const double &value){
    _last_factor_changes[index] = _factor_changes[index];
    _factor_changes[index] = _factors[index];
    _factors[index] = value;
    set_output_refresh();
  }

  template <class B>
  void Neuron<B>::set_factors(const vector<double> &factors){
    _last_factor_changes = _factor_changes;
    _factor_changes = _factors;
    _factors = factors;
    set_output_refresh();
  }

  template <class B>
  void Neuron<B>::enable_bias() {
    if(not bias_enabled()) _bias_enabled = true;
  }

  template <class B>
  void Neuron<B>::disable_bias() {
    if(bias_enabled()) _bias_enabled = false;
  }

  template <class B>
  void Neuron<B>::set_bias(const double &value){
    _last_bias_change = _bias_change;
    _bias_change = _bias;
    _bias = value;
    set_output_refresh();
  }

  template <class B>
  void Neuron<B>::set_before_layer(shared_ptr<vector<B>> layer) {
    _before_layer = layer;
    resize(layer.size());
    set_output_refresh();
  }

  template <class B>
  void Neuron<B>::set_delta(const double &delta) {
    _delta = delta;
  }

  template <class B>
  double Neuron<B>::output() {
    if(need_refresh()) refresh();
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
  int Neuron<B>::factors_size() const {
    return _factors.size();
  }

  template <class B>
  const vector<double>& Neuron<B>::factors() const {
    return _factors;
  }

  template <class B>
  const vector<double>& Neuron<B>::factor_changes() const {
    return _factor_changes;
  }

  template <class B>
  const vector<double>& Neuron<B>::last_factor_changes() const {
    return _last_factor_changes;
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

  template <class B>
  double Neuron<B>::delta() const {
    return _delta;
  }

  template <class B>
  shared_ptr<vector<B>> Neuron<B>::before_layer() const {
    return _before_layer();
  }

  template <class B>
  void Neuron<B>::set_output_refresh() {
    _refresh_output = true;
  }

  template <class B>
  void Neuron<B>::unset_output_refresh() {
    _refresh_output = false;
  }

  template <class B>
  bool Neuron<B>::need_refresh() {
    return _refresh_output;
  }

  template <class B>
  Neuron<B>::~Neuron() {
  }
}
