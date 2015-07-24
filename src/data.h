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
#ifndef ___DATA___
#define ___DATA___
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

namespace mp {
  class data {
    public:
      data();
      data(const string &path);

      unsigned int inputs_length() const;
      unsigned int outputs_length() const;
      unsigned int elements() const;

      weak_ptr<vector<double>> input(const unsigned int &index);
      weak_ptr<vector<double>> output(const unsigned int &index);
      void reload(const string &path);

    private:
      unsigned int _inputs_length;
      unsigned int _outputs_length;
      unsigned int _elements;

      vector<shared_ptr<vector<double>>> _inputs;
      vector<shared_ptr<vector<double>>> _outputs;

      vector<string> split_string(const string &s, const char &delimiter);
  };
}
#endif
