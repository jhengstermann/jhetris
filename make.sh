#!/bin/bash

cd build
rm -f *.o 
rm app
gcc -Wall -c ../src/block.c ../src/board.c ../src/display.c ../src/main.c
gcc block.o display.o board.o main.o -lncurses -o app                              