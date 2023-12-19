#!/bin/sh

rm -rf rp2040-build
mkdir rp2040-build
cd rp2040-build
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DPICO_SDK_PATH=~/pico/pico-sdk -DPICO_EXTRAS_PATH=~/pico/pico-extras ..
