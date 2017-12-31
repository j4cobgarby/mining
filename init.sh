#!/bin/bash

# Initialises the build directory and makefiles

mkdir -p build
cd build

cmake ../src
echo "Initialised. Do you want to BUILD IT?"
read -p "(y/n) " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo `pwd`
    /bin/bash ../run.sh
fi

cd ..
