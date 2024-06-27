#!/bin/bash

if [ ! -d ./target ]; then
    mkdir ./target
fi

if [ ! -d /build ]; then
    mkdir -p ./build/debug
fi
