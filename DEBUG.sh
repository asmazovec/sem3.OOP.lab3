#!/bin/sh
NAME=sem3.OOP.lab2

if ! [ -d ./bin ]; then
    mkdir bin;
fi
echo `pwd`\/bin\/$NAME
echo

g++ vector.cpp matrix.cpp main.cpp -D DEBUG -O3 -o ./bin/$NAME &&
./bin/$NAME


