#!/bin/bash

# Install dependencies
sudo apt-get install cmake googletest valgrind

# Install gtest
cd /usr/src/googletest
sudo mkdir build
cd build
sudo cmake ..
sudo make
sudo make install

