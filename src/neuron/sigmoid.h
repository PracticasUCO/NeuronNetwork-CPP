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
#ifndef ___SIGMOID__NEURON___
#define ___SIGMOID__NEURON___
#include <vector>
#include <memory>
#include <cmath>
#include "base.h"

namespace mp { // Stands for Multilayer Perceptron
  namespace neuron { // Neuron's namespace

    class sigmoid : public mp::neuron::base {
      public:
        // Empty constructor
        sigmoid();

        // Fill constructor
        sigmoid(const unsigned int &inputs_size, const bool &bias_enabled);

        // Copy constructor
        sigmoid(const base &n);

        // Destructor
        ~sigmoid();

      protected:
        double calculate_output(const std::vector<double> &input_layer) override;
        double calculate_output(const std::vector<std::shared_ptr<base>> &neuron_layer) override;
    };
  }
}

#endif
