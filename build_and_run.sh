#!/bin/bash
(
if [ ! -d "out/" ]; then
  mkdir out/
fi
cd out/
cmake -DCMAKE_BUILD_TYPE=Debug -S ../ -B . -G Ninja
ninja
./gamez
)
