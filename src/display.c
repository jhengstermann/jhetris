
#include <stdio.h>

#include <ncurses.h>

#include "display.h"

// #define DISABLE_GAME_DISPLAY

// #define clear()      printf("\033[H\033[J")
// #define gotoxy(xPos, yPos) printf("\033[%d;%dH", (yPos), (xPos))
// #define gotoxy(xPos, yPos) move(yPos, xPos);

#define C_PRINT(COLOR, TO_PRINT)  \
    do {                          \
        change_color(COLOR);      \
        printf("%c", TO_PRINT);   \
        change_color(EMPTY_TILE); \
    } while (0)

void change_color(block_type b_t) {
    switch (b_t) {
    case EMPTY_TILE:
        printf("\033[39m");
        break;

    case L_BLOCK:
        printf("\033[93m");
        break;

    case J_BLOCK:
        printf("\033[94m");
        break;

    case I_BLOCK:
        printf("\033[96m");
        break;

    case T_BLOCK:
        printf("\033[95m");
        break;

    case S_BLOCK:
        printf("\033[92m");
        break;

    case Z_BLOCK:
        printf("\033[31m");
        break;

    case O_BLOCK:
        printf("\033[33m");
        break;

    default:
        break;
    }
}

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

block_type current_screen[BOARD_WIDTH][BOARD_HEIGHT];

int offset_x = 60, offset_y = 5;

void clear_display() {

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {

#ifndef DISABLE_GAME_DISPLAY
            gotoxy(x + offset_x, y + offset_y);
            // printf("%c", '.');
            C_PRINT(EMPTY_TILE, '.');
#endif
            current_screen[x][y] = EMPTY_TILE;
        }
    }
    gotoxy(0, 0);
}

void update_display(block_type board[BOARD_WIDTH][BOARD_HEIGHT]) {

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {

            if (current_screen[x][y] != board[x][y]) {

#ifndef DISABLE_GAME_DISPLAY
                gotoxy(x + offset_x, y + offset_y);
                // printf("%c", board[x][y] ? '#' : '.');
                C_PRINT(board[x][y], board[x][y] ? '#' : '.');
#endif

                current_screen[x][y] = board[x][y];
            }
        }
    }
    gotoxy(0, 0);
}

void draw_block(block b) {

    for (int i = 0; i < 4; i++) {

#ifndef DISABLE_GAME_DISPLAY
        gotoxy(b.tiles[i].x + offset_x, b.tiles[i].y + offset_y);
        // printf("O");
        C_PRINT(b.type, '0');
#endif

    }
    gotoxy(0, 0);
}

void undraw_block(block b) {

    for (int i = 0; i < 4; i++) {

#ifndef DISABLE_GAME_DISPLAY
        gotoxy(b.tiles[i].x + offset_x, b.tiles[i].y + offset_y);
        // printf("%c", '.');
        C_PRINT(EMPTY_TILE, '.');
#endif

    }
    gotoxy(0, 0);
}