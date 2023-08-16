
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "term.h"
#include "board.h"

int main() {

    printf("hello world\n");

    // time_t t;
    // srand((unsigned) time(&t));

    /*
     * Manual Game
     */

#ifdef __unix
    // setup for ncurses
    WINDOW *w = initscr();
    cbreak();
    nodelay(w, TRUE);
#endif

    char c;
    c = GET_KEY();

    input_t control = NO_INPUT;

    // new game
    new_game();
    int score = 0;

    while (1) {
        c = getch();
        if (c != -1) {
            if (c == 'a')
                control = LEFT;
            else if (c == 'd')
                control = RIGHT;
            else if (c == 'w')
                control = ROTATE;
            else if (c == 's')
                control = DOWN;
        }
        if (!board_update(control, &score)) {
            break;
        }

        control = NO_INPUT;
    }
    clear();
    gotoxy(1, 1);
    printf("game over, score: %d\n", score);

    /* end of manual Game */

    return 0;
}