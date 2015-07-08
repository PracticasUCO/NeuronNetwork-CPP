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
#ifndef ___NEURON___
#define ___NEURON___
#include <vector>
#include <memory>

namespace mp { // Stands for MultilayerPerceptron
  namespace neuron { //Neuron's namespace
    /**
     * \class base base.h
     * \brief This class represents a neuron's base in the network. Each neuron have an arbitrary
     *  number of inputs, a bias (that can be active or not) and a delta.
     *
     * A neuron's base is a class that represent the basic unit of neuron network. Each neuron
     * receives an arbitrary number of inputs, process it, and return a value between 0 and 1.
     *
     * A neuron's base can process a variable number of inputs. The inputs must have a double
     * type, or a mp:neuron:base * type.
     *
     * \note This class can not be instanciated You are enforced to use a derived class.
     * derived class must implement a method called calculate_output.
     * */
    class base {
      public:

        /**
         * \brief It builds a neuron with bias disabled and zero factor's length
         * **/
        base();

        /**
         * \brief It initializes a neuron with the given factors_size and with bias_enabled.
         * \param factors_size the length of the given factors
         * \param bias_enables indicates if the bias is enabled or not
         * */
        base(const int &factors_size, const bool &bias_enabled);

        /**
         * \brief It creates a copy of the given neuron.
         * \param n the neuron to be copied
         * **/
        base(const base &n);

        /**
         * \brief It resizes the neuron to have the factors_size length.
         * \param factors_size the size of the factors to this neuron
         * */
        void resize(const unsigned int &factors_size);

        /**
         * \brief It sets a factor of the given neuron at the given index
         * \param index the position where the factor is set
         * \param value new factor's value
         * */
        void set_factor(const unsigned int &index, const double &value);

        /**
         * \brief It sets a new set of factors to the given neuron.
         * \param factors a vector with all new factors
         * */
        void set_factors(const std::vector<double> &factors);

        /**
         * \brief It enables the neuron bias if it is disabled
         * **/
        void enable_bias();

        /**
         * \brief It disables the neuron bias if it is enabled
         * **/
        void disable_bias();

        /**
         * \brief It sets a new bias value if bias is enabled, otherwise it does nothing.
         * \param value the new bias value
         * */
        void set_bias(const double &value);

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
        double output() const;

        /**
         * \brief It returns the specified factor applied to the neuron's input
         * \param index index of the neuron's factor
         * \return the neuron's factor specified at the given index.
         * */
        double factor(const unsigned int &index) const;

        /**
         * \brief It returns the factor change applied to the neuron's input
         * \param index index of the neuron's factor
         * \return the change made to the neuron's factor
         * */
        double factor_change(const unsigned int &index) const;

        /**
         * \brief It returns the last factor change applied to the neuron's input
         * \param index index of the neuron's factor
         * \return the last change made to the neuron's factor
         * */
        double last_factor_change(const unsigned int &index) const;

        /**
         * \brief It returns the number of factors in the neuron
         * \return the factor's size
         * **/
        unsigned int factors_size() const;

        /**
         * \brief It returns the list of factors of this neuron
         * \return a vector with all of the factors of this neuron.
         * **/
        const std::vector<double>& factors() const;

        /**
         * \brief It returns the list of factor changes in this neuron.
         * \return a vector with all factor changes on this neuron.
         * **/
        const std::vector<double>& factor_changes() const;


        /**
         * \brief It returns the list of last factor changes in this neuron.
         * \return a vector with all last factor changes on this neuron.
         * **/
        const std::vector<double>& last_factor_changes() const;

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
         * \brief It refresh the neuron output if needed
         * */
        void refresh(const std::vector<double> &input_layer);
        void refresh(const std::vector<std::shared_ptr<base>> &neuron_layer);

        ~base();

      protected:
        virtual double calculate_output(const std::vector<double> &input_layer) =0;
        virtual double calculate_output(const std::vector<std::shared_ptr<base>> &neuron_layer) =0;

      private:
        std::vector<double> _factors;
        std::vector<double> _factor_changes;
        std::vector<double> _last_factor_changes;
        double _bias;
        double _bias_change;
        double _last_bias_change;
        bool _bias_enabled;
        double _delta;
        double _output;
    }; // Base Class

  } // namespace neuron

} // namespace mp
#endif
