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
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include "network.h"
#include "data.h"

using namespace std;
using namespace mp;

struct IMCConfig {
  IMCConfig() {
    externalIterations = 1000;
    hiddenLayers = 1;
    hiddenNeurons = 5;
    learning_factor = 0.9;
    momentum_factor = 0.1;
    bias = true;
  }

  string trainFile;
  string testFile;
  data trainData;
  data testData;
  unsigned int externalIterations;
  unsigned int hiddenLayers;
  unsigned int hiddenNeurons;
  double learning_factor;
  double momentum_factor;
  bool bias;
};

void print_config(const struct IMCConfig &conf) {
  cout << "Train file: " << conf.trainFile << endl;
  cout << "Test file: " << conf.testFile << endl;
  cout << "Iterations: " << conf.externalIterations << endl;
  cout << "Hidden layers: " << conf.hiddenLayers << endl;
  cout << "Hidden neurons: " << conf.hiddenNeurons << endl;
  cout << "Learning factor: " << conf.learning_factor << endl;
  cout << "Momentum factor: " << conf.momentum_factor << endl;
  cout << "Bias: " << ( conf.bias ? "true" : "false" ) << endl;
}

bool exists_file(const string &file) {
  ifstream f( file.c_str() );

  if( f.good() ) {
    f.close();
    return true;
  } else {
    f.close();
    return false;
  }
}

void check_configuration(struct IMCConfig conf) {
  bool good_config = true;

  if( conf.trainFile.empty() ) {
    cerr << "Train file hasn't been specified (use -t /path/to/train/file)" << endl;
    good_config = false;
  } else {
    if( exists_file( conf.trainFile )) {
      conf.trainData.reload( conf.trainFile );

      if( conf.trainData.elements() == 0 ) {
        cerr << "Train data empty or invalid." << endl;
        good_config = false;
      }
    } else {
      cerr << conf.trainFile << " does not exist." << endl;
      good_config = false;
    }
  }

  if( conf.testFile.empty() ) {
    cerr << "Test file hasn't been specified (use -T /path/to/test/file)" << endl;
    good_config = false;
  } else {
    if( exists_file( conf.testFile ) ) {
      conf.testData.reload( conf.testFile );

      if( conf.testData.elements() == 0 ) {
        cerr << "Test data empty or invalid." << endl;
        good_config = false;
      }
    } else {
      cerr << conf.testFile << " does not exist." << endl;
      good_config = false;
    }
  }

  if(( !conf.trainFile.empty() ) && ( conf.trainFile == conf.testFile )) {
    cerr << "WARNING: Your are using the same file to train and test the network." << endl;
    cerr << conf.trainFile << " is used twice." << endl << endl;
  }

  if( !good_config ) {
    cerr << "Use --help to read the help" << endl;
    exit( EXIT_FAILURE );
  }
}

void license_disclaimer() {
  cout << "NeuronNetwork-CPP" << endl;
  cout << "Copyright (C) 2015  Pedro José Piquero Plaza <gowikel@gmail.com>" << endl;
  cout << endl;

  cout << "This program is free software: you can redistribute it and/or modify" << endl;
  cout << "it under the terms of the GNU Affero General Public License as published by" << endl;
  cout << "the Free Software Foundation, either version 3 of the License, or" << endl;
  cout << "any later version." << endl;
  cout << endl;

  cout << "This program is distributed in the hope that it will be useful," << endl;
  cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << endl;
  cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << endl;
  cout << "GNU Affero General Public License for more details." << endl;
  cout << endl;

  cout << "You should have received a copy of the GNU Affero General Public License" << endl;
  cout << "along with this program.  If not, see <http://www.gnu.org/licenses/>." << endl;
  cout << endl;
}

int main(int argc, char ** argv) {
  struct IMCConfig conf;

  // Parse configuration
  for(int i = 1; i < argc; i++) {
    if( strcmp( argv[i], "-t" ) == 0 ) {
      i++;
      conf.trainFile = argv[i];
    } else if( strcmp( argv[i], "-T" ) == 0 ) {
      i++;
      conf.testFile = argv[i];
    } else if( strcmp( argv[i], "-i" ) == 0 ) {
      i++;
      conf.externalIterations = (unsigned int) atoi(argv[i]);
    } else if( strcmp( argv[i], "-l" ) == 0 ) {
      i++;
      conf.hiddenLayers = (unsigned int) atoi(argv[i]);
    } else if( strcmp( argv[i], "-h" ) == 0 ) {
      i++;
      conf.hiddenNeurons = (unsigned int) atoi(argv[i]);
    } else if( strcmp( argv[i], "-e" ) == 0 ) {
      i++;
      conf.learning_factor = atof( argv[i] );
    } else if( strcmp( argv[i], "-m" ) == 0 ) {
      i++;
      conf.momentum_factor = atof( argv[i] );
    } else if( strcmp( argv[i], "-b" ) == 0 ) {
      conf.bias = false;
    } else if( strcmp( argv[i], "--help" ) == 0 ) {
      cout << "IMC (Introducción a los Modelos Computacionales)" << endl;
      cout << "Usage: imc -t /path/to/train -T /path/to/test [options]" << endl;
      cout << endl;

      cout << "NN options:" << endl;
      cout << "\t -t: path to train file" << endl;
      cout << "\t -T: path to test file" << endl;
      cout << "\t -i: max number of times to repeat backpropagation (default 1000)." << endl;
      cout << "\t -l: number of hidden layers (default 1)." << endl;
      cout << "\t -h: number of hidden neurons (default 5)." << endl;
      cout << "\t -e: learning factor (aka eta, default 0.9)" << endl;
      cout << "\t -m: momentum factor (aka mu, default 0.1)" << endl;
      cout << "\t -b: disable bias" << endl;
      cout << "\t --help: this help" << endl;
      cout << endl;

      cout << "-t and -T options must be specified" << endl;
      return  EXIT_SUCCESS;
    }
  }

  license_disclaimer();

  // Configure app
  check_configuration( conf );
  print_config( conf );

  return EXIT_SUCCESS;
}
