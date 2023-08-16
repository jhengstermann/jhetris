#include "term.h"

#ifdef __unix
void gotoxy(int x, int y)
{
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}
#else
void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
int win_GET_KEY()
{
    if (kbhit())
        return getch();
    else
        return -1;
}
#endif