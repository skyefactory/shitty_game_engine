#!/bin/bash

rm -rf build/windows
cmake -B build/windows -S . -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake
cmake --build build/windows