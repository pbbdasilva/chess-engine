#!/bin/bash

CCOMP="g++"
FILE="*.cpp"
CFLAGS="-std=c++17"
FLAGS="-o"
EXE="main"

$CCOMP $FILE $CFLAGS $FLAGS $EXE
