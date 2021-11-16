#!/bin/bash

CCOMP="g++"
FILE="./src/*.cpp"
CFLAGS="-std=c++17"
FLAGS="-o"
EXE="main"

$CCOMP $FILE $CFLAGS $FLAGS $EXE
