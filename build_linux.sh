#!/bin/bash

# TD Animation Plugin Build Script
# For Linux (32-bit)

echo "========================================"
echo "Building TD Animation Plugin..."
echo "========================================"

# Clean previous build
rm -rf build
mkdir -p build
cd build

# Create output directory
mkdir -p bin

# Compile source files
echo "Compiling TDAnimation.cpp..."
g++ -c -std=c++17 -m32 -fPIC -O3 -I../SDK -I.. ../TDAnimation.cpp -o TDAnimation.o

if [ $? -ne 0 ]; then
    echo "Error compiling TDAnimation.cpp"
    exit 1
fi

echo "Compiling main.cpp..."
g++ -c -std=c++17 -m32 -fPIC -O3 -I../SDK -I.. ../main.cpp -o main.o

if [ $? -ne 0 ]; then
    echo "Error compiling main.cpp"
    exit 1
fi

# Link the plugin
echo "Linking plugin..."
g++ -m32 -shared -fPIC -pthread -o bin/td_animation.so TDAnimation.o main.o

if [ $? -ne 0 ]; then
    echo "Error linking plugin"
    exit 1
fi

echo "========================================"
echo "Build successful!"
echo "Plugin: build/bin/td_animation.so"
echo "========================================"

# Copy include file
cp ../td_animation_plugin.inc bin/

echo "Include file copied to build/bin/"
