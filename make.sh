#!/bin/bash

cd build
rm jhetris

gcc -Wall ../src/term.c ../src/block.c ../src/board.c ../src/display.c ../src/main.c -lncurses -o jhetris