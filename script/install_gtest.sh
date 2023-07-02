#!/bin/bash

sudo apt-get install cmake
sudo apt-get install libgtest-dev googletest
cd /usr/src/gtest
sudo cmake -Bbuild
sudo cmake --build build
sudo cp ./build/lib/libgtest* /usr/lib

# export CXX="/usr/bin/c++"
# cd res
# tar xf release-1.8.0.tar.gz
# mv googletest-release-1.8.0 gtest
# cd gtest
# sudo cmake -DBUILD_SHARED_LIBS=ON .
# sudo make
# sudo cp -a googletest/include/gtest /usr/include
# sudo cp -a googlemock/gtest/libgtest_main.so googlemock/gtest/libgtest.so /usr/lib/ 
# sudo cp -a googlemock/gtest/libgtest_main.so googlemock/gtest/libgtest.so ..
# sudo make install
