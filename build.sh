#!/bin/bash

mkdir -p build
cd build

cmake -G Ninja \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      ..

ninja

cp compile_commands.json ..
