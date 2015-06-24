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
- <a href="https://github.com/PracticasUCO/NeuronNetwork-CPP/blob/master/neuron.cpp">neuron.h</a>
contains the definition of a neuron base. It is defined as a pure virtual class, so all neurons must
inherit from this class and redefine the refresh method.
- <a href="https://github.com/PracticasUCO/NeuronNetwork-CPP/blob/master/sigmoid_neuron.h">sigmoid_neuron.h</a> contains the definition of a sigmoid neuron.

# Dependencies
The project is writed in ANSI C++ 2014 and it is not compatible with earlier standards, so you need
to use a modern compiler. I used clang++, but if you prefer g++, simply change it in the makefile.

There is not other dependencies in the project.

# There is a better way to do...
I am always trying to improve my skills, so if you think that I did something wrong, or it can
be do better, please make a new issue or a merge request.

# License
The MIT License (MIT)

Copyright (c) 2015 Pedro José Piquero Plaza

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
