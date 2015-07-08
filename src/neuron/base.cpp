#include "base.h"

namespace mp {
  namespace neuron {
    base::base() {
      _bias = 0.0;
      _bias_change = 0.0;
      _last_bias_change = 0.0;
      _delta = 0.0;
      _bias_enabled = false;
    }

    base::base(const int &factors_size, const bool &bias_enabled) {
      _bias_enabled = bias_enabled;
      _bias = 0.0;
      _bias_change = 0.0;
      _last_bias_change = 0.0;
      _delta = 0.0;
      resize(factors_size);
    }

    base::base(const base& n) {
      set_delta(n.delta());

      set_factors(n.last_factor_changes());
      set_factors(n.factor_changes());
      set_factors(n.factors());

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

    void base::resize(const unsigned int &factors_size) {
      _factors.resize(factors_size, 0.0);
      _factor_changes.resize(factors_size, 0.0);
      _last_factor_changes.resize(factors_size, 0.0);
    }

    void base::set_factor(const unsigned int &index, const double &value) {
      _last_factor_changes[index] = _factor_changes[index];
      _factor_changes[index] = _factors[index];
      _factors[index] = value;
    }

    void base::set_factors(const std::vector<double> &factors) {
      _last_factor_changes = _factor_changes;
      _factor_changes = _factors;
      _factors = factors;
    }

    void base::enable_bias() {
      if(not bias_enabled()) _bias_enabled = true;
    }

    void base::disable_bias() {
      if(bias_enabled()) _bias_enabled = false;
    }

    void base::set_bias(const double &value) {
      if(bias_enabled()) {
        _last_bias_change = _bias_change;
        _bias_change = _bias;
        _bias = value;
      }
    }

    void base::set_delta(const double &delta) {
      _delta = delta;
    }

    double base::output() const {
      return _output;
    }

    double base::factor(const unsigned int &index) const {
      return _factors[index];
    }

    double base::factor_change(const unsigned int &index) const {
      return _factor_changes[index];
    }

    double base::last_factor_change(const unsigned int &index) const {
      return _last_factor_changes[index];
    }

    unsigned int base::factors_size() const {
      return _factors.size();
    }

    const std::vector<double>& base::factors() const {
      return _factors;
    }

    const std::vector<double>& base::factor_changes() const {
      return _factor_changes;
    }

    const std::vector<double>& base::last_factor_changes() const {
      return _last_factor_changes;
    }

    bool base::bias_enabled() const {
      return _bias_enabled;
    }

    double base::bias() const {
      if(bias_enabled()) return _bias;
      else return 0.0;
    }

    double base::bias_change() const {
      if(bias_enabled()) return _bias_change;
      else return 0.0;
    }

    double base::last_bias_change() const {
      if(bias_enabled()) return _last_bias_change;
      else return 0.0;
    }

    double base::delta() const {
      return _delta;
    }

    void base::refresh(const std::vector<double> &input_layer) {
      _output = calculate_output(input_layer);
    }

    void base::refresh(const std::vector<base *> &neuron_layer) {
      _output = calculate_output(neuron_layer);
    }

    base::~base() {
    }
  }
}
