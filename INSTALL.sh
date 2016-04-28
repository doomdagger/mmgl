#!/bin/sh

# create and change to build directory
mkdir build && cd build

# execute cmake, attention: two points here
cmake ..

# execute make
make

# install project, default installation path is /usr/local/include and /usr/local/lib
make install
