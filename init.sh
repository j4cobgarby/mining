#!/bin/bash

# Initialises the build directory and makefiles

mkdir -p build
cd build

cmake ../src
echo "Initialised. Build it with "

cd ..
