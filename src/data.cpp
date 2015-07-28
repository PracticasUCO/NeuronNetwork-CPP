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
#include "data.h"

namespace mp {
  data::data() {
    _inputs_length = 0;
    _outputs_length = 0;
    _elements = 0;
  }

  data::data(const std::string &path) {
    reload(path);
  }

  unsigned int data::inputs_length() const {
    return _inputs_length;
  }

  unsigned int data::outputs_length() const {
    return _outputs_length;
  }

  unsigned int data::elements() const {
    return _elements;
  }

  weak_ptr<vector<double>> data::input(const unsigned int &index) const {
    return weak_ptr<vector<double>>(_inputs.at( index ));
  }

  weak_ptr<vector<double>> data::output(const unsigned int &index) const {
    return weak_ptr<vector<double>>(_outputs.at( index ));
  }

  void data::reload(const string &path) {
    ifstream file;
    file.open( path );

    if( file.is_open() ) {
      string header;
      getline(file, header);
      sscanf(header.c_str(), "%u %u %u", &_inputs_length, &_outputs_length, &_elements);

      _inputs.clear();
      _outputs.clear();

      _inputs.reserve( _elements );
      _outputs.reserve( _elements );

      for(unsigned int i = 0; i < _elements; i++) {
        string line;
        shared_ptr<vector<double>> input(new vector<double>());
        shared_ptr<vector<double>> output(new vector<double>());

        input->reserve( _inputs_length );
        output->reserve( _outputs_length );

        getline(file, line);
        auto values = split_string( line, ' ' );

        for(unsigned int j = 0; j < values.size(); j++) {
          if( j < _inputs_length ) {
            input->push_back( stod( values.at( j ) ) );
          }
          else {
            output->push_back( stod( values.at( j ) ) );
          }
        }
        _inputs.push_back(input);
        _outputs.push_back(output);
      }
    }
  }

  vector<string> data::split_string(const string &s, const char &delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }
}
