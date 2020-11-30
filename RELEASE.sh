#!/bin/sh
NAME=sem3.OOP.lab2

if ! [ -d ./bin ]; then
    mkdir bin;
fi

g++ vector.cpp matrix.cpp main.cpp -o ./bin/$NAME &&
./bin/$NAME


