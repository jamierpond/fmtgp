#!/bin/bash
set -e

# compiles main.cpp, link against std lib
mkdir -p build
echo "Compiling main.cpp"
rm -rf build/main
clang main.cpp -std=c++20 -O3 -fvectorize -mfloat-abi=hard -mfpu=neon -lstdc++ -o build/main

echo "Running main"
./build/main
