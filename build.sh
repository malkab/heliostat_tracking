#!/bin/bash

# A shortcut script to build the project
rm build/libbluesolarangles.so*
rm build/libbluesolarangles.a
cmake -S . -B build
cd build
make