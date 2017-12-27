#!/bin/bash

# Runs the exectuable and redirects the output to a log file

cd build

make -j6

echo "RESTART ============================" >> miner.log
echo `date` >> miner.log
./miner | tee -a miner.log
echo "Logged to build/miner.log"

cd ..
