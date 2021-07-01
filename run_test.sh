#!/bin/bash
# Script to run quad_test
rm -rf build
mkdir build
cd build
printf "\n[BUILD CMAKE FILES] \n\n"
cmake ..
printf "\n[BUILD TARGET QUAD_TEST] \n"
make -j
printf "\n\n[TESTING QUADTREE] \n\n"
./quad_test