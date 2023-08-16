cd build
rm app.exe
gcc -Wall ../src/block.c ../src/board.c ../src/display.c ../src/main.c ../src/term.c -o app.exe
cd ..