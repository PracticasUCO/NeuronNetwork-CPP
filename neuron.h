#ifndef ___NEURON__CPP___
#define ___NEURON__CPP___
#include <vector>

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
       * \brief It initializes a neuron with the given inputs_size and with bias_enabled.
       * \param inputs_size the length of the given inputs
       * \param bias_enables indicates if the bias is enabled or not
       * */
      Neuron(const int &inputs_size, const bool bias_enabled);

      /**
       * \brief It resizes the neuron to have the inputs_size length. Notice that all original inputs
       * will be lost, with their respective changes.
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
       * \brief It sets a new bias value
       * \param value the new bias value
       * */
      void set_bias(const double &value);

      /**
       * \brief It sets a pointer to the layer that is before this neuron. The
       * layer will influence this neuron in its outputs.
       * \param layer the layer that is before this neuron.
       * */
      void set_before_layer(vector<B> &layer);

      /**
       * \brief It returns the neuron output.
       * \return the output of this neuron.
       * */
      double output() const;

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
       * \brief It refresh the neuron output if needed
       * \return the new output value after refresh it.
       * */
      virtual double refresh() =0;

    protected:
      /**
       * \brief It sets the refresh output flag to true.
       * */
      void set_output_refresh();

    private:
      vector<B> * _before_layer;
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
       * \brief It sets the refresh output flag to false.
       * */
      void unset_output_refresh();

      /**
       * \brief It checks if the output needs a refresh.
       * \return true if the neuron must call to refresh to update the output, false otherwise
       * */
      bool need_refresh();
  };
}
#endif
