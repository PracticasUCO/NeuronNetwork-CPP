#ifndef ___NEURON__CPP___
#define ___NEURON__CPP___
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

namespace mp { // Stands for MultilayerPerceptron
  /**
   * \class Neuron neuron.h neuron.cpp
   * \brief This class represents a neuron in the network. Each neuron have an arbitrary number of
   * inputs, a bias (that can be active or not) and a delta.
   *
   * A neuron is a class that represent the basic unit of neuron network. Each neuron receives
   * an arbitrary number of inputs, process it, and return a value between 0 and 1.
   *
   * A neuron can have an array of doubles or an array of another neuros as inputs.
   * \note This class can not be instanciated You are enforced to use a derived class.
   * derived class must implement a method called refresh (used to propagate the outputs
   * throw the network).
   * */
  template <class B>
  class Neuron {
    public:
      /**
       * \brief It builds a neuron with bias disabled and zero inputs
       * **/
      Neuron();

      /**
       * \brief It initializes a neuron with the given inputs_size and with bias_enabled.
       * \param inputs_size the length of the given inputs
       * \param bias_enables indicates if the bias is enabled or not
       * */
      Neuron(const int &inputs_size, const bool bias_enabled);

      /**
       * \brief It creates a copy of the given neuron.
       * \param n the neuron to be copied
       * **/
      Neuron(const Neuron<B> &n);

      /**
       * \brief It resizes the neuron to have the inputs_size length.
       * \param inputs_size the size of the inputs to this neuron
       * */
      void resize(const int &inputs_size);

      /**
       * \brief It sets a factor of the given neuron at the given index
       * \param index the position where the factor is set
       * \param value new factor's value
       * */
      void set_factor(const int &index, const double &value);

      /**
       * \brief It sets a new set of factors to the given neuron.
       * \param factors a vector with all new factors
       * */
      void set_factors(const vector<double> &factors);

      /**
       * \brief It enables the neuron bias if it is disabled
       * **/
      void enable_bias();

      /**
       * \brief It disables the neuron bias if it is enabled
       * **/
      void disable_bias();

      /**
       * \brief It sets a new bias value
       * \param value the new bias value
       * */
      void set_bias(const double &value);

      /**
       * \brief It sets a pointer to the layer that is before this neuron. The
       * layer will influence this neuron in its outputs.
       * Notice that the factor's size will be set accordingly with the size
       * of the layer that is set.
       * \param layer the layer that is before this neuron.
       * */
      void set_before_layer(shared_ptr<vector<B>> layer);

      /**
       * \brief It sets how much the neuron will try to fix its own errors.
       * \param delta a value between 0 and 1 that specify how much the neuron will try to fix its
       * own errors (0 it will not try, 1 it will do it completly)
       * **/
      void set_delta(const double &delta);

      /**
       * \brief It returns the neuron output. It refresh the output if needed.
       * \return the output of this neuron.
       * */
      double output();

      /**
       * \brief It returns the specified factor applied to the neuron's input
       * \param index index of the neuron's factor
       * \return the neuron's factor specified at the given index.
       * */
      double factor(const int &index) const;

      /**
       * \brief It returns the factor change applied to the neuron's input
       * \param index index of the neuron's factor
       * \return the change made to the neuron's factor
       * */
      double factor_change(const int &index) const;

      /**
       * \brief It returns the last factor change applied to the neuron's input
       * \param index index of the neuron's factor
       * \return the last change made to the neuron's factor
       * */
      double last_factor_change(const int &index) const;

      /**
       * \brief It returns the number of factors in the neuron
       * \return the factor's size
       * **/
      int factors_size() const;

      /**
       * \brief It returns the list of factors of this neuron
       * \return a vector with all of the factors of this neuron.
       * **/
      const vector<double>& factors() const;

      /**
       * \brief It returns the list of factor changes in this neuron.
       * \return a vector with all factor changes on this neuron.
       * **/
      const vector<double>& factor_changes() const;

      /**
       * \brief It returns the list of last factor changes in this neuron.
       * \return a vector with all last factor changes on this neuron.
       * **/
      const vector<double>& last_factor_changes() const;

      /**
       * \brief It checks if the neuron have a bias enabled.
       * \return a true value if the bias is enabled, false otherwise
       * */
      bool bias_enabled() const;

      /**
       * \brief It returns the bias value if it is enabled, zero otherwise.
       * \return the bias value if it is enabled, zero otherwise.
       * */
      double bias() const;

      /**
       * \brief It returns the bias change if bias is enabled, zero otherwise.
       * \return the bias change if it is enabled, zero otherwise.
       * */
      double bias_change() const;

      /**
       * \brief It returns the last bias change if bias is enabled, zero otherwise.
       * \return the last bias change if bias is enabled, zero otherwise.
       * */
      double last_bias_change() const;

      /**
       * \brief It returns the neuron's delta
       * \return The neuron's delta
       * **/
      double delta() const;

      /**
       * \brief It returns the before layer of this neuron
       * \return the before layer of this neuron.
       * **/
      shared_ptr<vector<B>> before_layer() const;

    protected:
      /**
       * \brief It refresh the neuron output if needed
       * \return the new output value after refresh it.
       * */
      virtual double refresh() =0;

      /**
       * \brief It sets the refresh output flag to true.
       * */
      void set_output_refresh();

      /**
       * \brief It sets the refresh output flag to false.
       * */
      void unset_output_refresh();

      ~Neuron();

    private:
      shared_ptr<vector<B>> _before_layer;
      vector<double> _factors;
      vector<double> _factor_changes;
      vector<double> _last_factor_changes;
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
      bool need_refresh();
  };
}
#endif
