# Neuron Network
This project tries to create a simple multilayer perceptron network. It was created in the
practices of the subject "Introduction to computer models" at Córdoba University in 2015.

As always, I tried to do my best to follow the object design, but it can have some errors because 
I don't have a full knowledge of the subject, and I don't now how this can change in the 
close future.

# A brief multilayer perceptron theory
A multilayer perceptron is a network that maps some input data in the apropiate outputs. Internally
it is constructed with neurons ordered in layers.

Each network must have the following layers:
- An input layer, that maps the network inputs.
- One or more hidden layers, that transform the input data.
- One output layer, that projects the output of the network.

And each layer can have one or more neurons (except the input layer, that have the real inputs of
the network). Each layer is fully connected with next one.

Each neuron process the information that receives from the layer where is connected with a nonlinear
function. Of course, the used function depends of the type of the neuron (for more details
<a href="https://github.com/PracticasUCO/NeuronNetwork-CPP/tree/readme-update#neuron-types">see Neuron types</a>).

The multilayer perceptron follows a tecnique called backpropagation to learn over the time (supervised learning).
As the output of a neuron, the backpropagation function will depend of the type of the neuron.

# Neuron types
## Sigmoid neuron
Is a nonlinear neuron that uses a logaritmic activation function. The output of the neuron n, in
the layer h is given by the following expresion:

<img src="http://www.sciweavers.org/tex2img.php?eq=output_%7Bn%7D%5E%7Bh%7D%20%3D%20%5Cfrac%7B1%7D%7B1%20%2B%20e%5E%7B-%28bias_%7Bn%7D%20%2B%20%5Csum_%7Bi%3D1%7D%5E%7Bn%7D%7Bfactor_%7Bi%7D%5E%7Bh%7Doutput_%7Bi%7D%5E%7Bh-1%7D%7D%20%29%7D%7D&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=0" align="center" border="0" alt="output_{n}^{h} = \frac{1}{1 + e^{-(bias_{n} + \sum_{i=1}^{n}{factor_{i}^{h}output_{i}^{h-1}} )}}" width="346" height="50" />

Where h is the layer index and n is the neuron index inside the layer.

# Project structure
The code is structured in 4 directories:
- <strong>bin:</strong> where all binaries must be set
- <strong>obj:</strong> where all c++ object must be set
- <strong>src:</strong> where all app's code must be set
- <strong>test:</strong> where all test must be set

The obj and bin directories are created by the makefile on demand, so you don't need to worry
about them. The src and test directories containt all the code of the application, in a organized
way.

# Dependencies
The project is written in ANSI C++ 2014 and I did not do any effort to make it compatible with earlier
standards, so you need to use a modern compiler. The compilers g++ and clang++ are good options to
compile the project, I used g++, but if you have another one, you can set it in the makefile.

I have also used the <a href="https://code.google.com/p/googletest/">Google Test Framework </a> to
test my app.

There is not other dependencies in the project.

# There is a better way to do...
I am always trying to improve my skills, so if you think that I did something wrong, or it can
be do better, please make a new issue or a merge request.

# License
<img src="http://www.gnu.org/graphics/agplv3-155x51.png"> </img> <br> <br>
NeuronNetwork-CPP
Copyright (C) 2015  Pedro José Piquero Plaza <gowikel@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the <a href="http://www.gnu.org/licenses/agpl.html">GNU Affero General Public License</a>
as published by the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


