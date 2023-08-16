#ifndef TERM_H
#define TERM_H

#ifdef __unix
    #include <ncurses.h>
    #define GET_KEY() getch()
    void gotoxy(int x, int y);
#else
    #include <windows.h>
    #include <conio.h>
    int win_GET_KEY();
    #define GET_KEY() win_GET_KEY()
    #define clear() system("cls")
    void gotoxy(int x, int y);
#endif

#endif