#!/bin/bash

cd build
rm -f *.o
rm app
gcc -Wall ../src/block.c ../src/board.c ../src/display.c ../src/main.c ../src/term.c -o main.exe
