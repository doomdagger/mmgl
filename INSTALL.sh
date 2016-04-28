#!/usr/bin/env bash

# create and change to build directory
BUILD_DIR="${PWD}/build"

if [ ! -d "$BUILD_DIR" ]; then
  mkdir -m 755 "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# execute cmake, attention: two points here
cmake ..

# execute make
make

# install project, default installation path is /usr/local/include and /usr/local/lib
sudo make install
