#!/bin/bash


sudo apt-get install cmake
sudo apt-get install googletest

cd /usr/src/googletest
sudo cmake -Bbuild
sudo cmake --build build
sudo cp /usr/src/googletest/build/googlemock/gtest/libgtest*.a /usr/lib
sudo cp /usr/src/googletest/build/googlemock/libgmock* /usr/lib
