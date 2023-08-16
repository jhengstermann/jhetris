
#include "board.h"

// #include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// sleep
// #include<windows.h>
#include <unistd.h>

#include "display.h"

#define GRAVITY 30 // ms

long long time_for_fall;

block_type board[BOARD_WIDTH][BOARD_HEIGHT];

block active_block;
int score;

long long millis() {
    struct timeval time;
    gettimeofday(&time, NULL); // get current time

    long long milliseconds = time.tv_sec * 1000LL + time.tv_usec / 1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

/* ----------------------------------------------------------------------- */

/*
 * function for:
 * - checking if block can move down
 * - moving a current active block down
 */
bool block_can_fall(block b) {

    for (int i = 0; i < 4; i++) {

        // check if block would collide at bottom
        if (b.tiles[i].y + 1 >= BOARD_HEIGHT) {
            return false;
        }

        // check if block would collide with old pieces
        if (board[b.tiles[i].x][b.tiles[i].y + 1] != 0) {
            return false;
        }
    }

    return true;
}
void current_block_down() {

    for (int i = 0; i < 4; i++) {
        active_block.tiles[i].y++;
    }
}

/* ----------------------------------------------------------------------- */

/*
 * function for:
 * - checking if block can rotate
 */
bool block_can_rotate(block b) {

    block rotated = block_rotate(b);

    for (int i = 0; i < 4; i++) {

        // check if block would collide with bottom
        if (rotated.tiles[i].y >= BOARD_HEIGHT) {
            return false;
        }

        // check if block would collide with border
        if ((rotated.tiles[i].x >= BOARD_WIDTH) || (rotated.tiles[i].x < 0)) {
            return false;
        }

        // check if block would collide with old pieces
        if (board[rotated.tiles[i].x][rotated.tiles[i].y] != 0) {
            return false;
        }
    }

    return true;
}

/* ----------------------------------------------------------------------- */

/*
 * function for:
 * - checking if block can move left/right
 */
bool block_can_move(block b, input_t direction) {
    if ((direction != LEFT) && (direction != RIGHT)) {
        // direction is invalid
        return false;
    }

    int x_offset = (direction == LEFT) ? -1 : 1;

    for (int i = 0; i < 4; i++) {

        // check if block would collide with border
        if ((b.tiles[i].x + x_offset >= BOARD_WIDTH) || (b.tiles[i].x + x_offset < 0)) {
            return false;
        }

        // check if block would collide with old pieces
        if (board[b.tiles[i].x + x_offset][b.tiles[i].y] != 0) {
            return false;
        }
    }

    return true;
}
void move_current_block(input_t direction) {
    if ((direction != LEFT) && (direction != RIGHT)) {
        // direction is invalid
        return;
    }

    int x_offset = (direction == LEFT) ? -1 : 1;

    for (int i = 0; i < 4; i++) {
        active_block.tiles[i].x += x_offset;
    }
}

/* ----------------------------------------------------------------------- */

void remove_full_lines() {
    int sum           = 0;
    int lines_removed = 0;

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        sum = 0;

        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (board[x][y] != 0) {
                sum++;
            }
        }
        if (sum == BOARD_WIDTH) {
            // line is full, move everything down
            for (int i = y; i > 0; i--) {
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    if (i != 0) {
                        board[x][i] = board[x][i - 1];
                    } else {
                        board[x][i] = EMPTY_TILE;
                    }
                }
            }
            lines_removed++;
        }

        if (lines_removed == 4) {
            score += 5;
        } else {
            score += lines_removed;
        }
        
        // TODO: decrease fall down timer
    }
}

long long set_fall_timer() {

    // TODO: get some dynamic fall down speed

    return millis() + 500;
}

void place_new_block() {
    active_block = new_block();

    active_block.center_coordinate.x = (int)(BOARD_WIDTH / 2);
    active_block.center_coordinate.y = (int)1;
    for (int i = 0; i < 4; i++) {
        active_block.tiles[i].x += active_block.center_coordinate.x;
        active_block.tiles[i].y += active_block.center_coordinate.y;
    }
}

void new_game() {
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            board[x][y] = EMPTY_TILE;
        }
    }

    clear_display();

    update_display(board);

    place_new_block();
    draw_block(active_block);

    time_for_fall = set_fall_timer();
}

bool game_over() {
    for (int i = 0; i < 4; i++) {
        // check if the active block hits anything
        if (board[active_block.tiles[i].x][active_block.tiles[i].y] != 0) {
            return true;
        }
    }

    return false;
}

bool board_update(input_t control, int *sc) {

    switch (control) {
    case LEFT:
    case RIGHT:
        if (block_can_move(active_block, control)) {
            undraw_block(active_block);
            move_current_block(control);
            draw_block(active_block);

            time_for_fall = set_fall_timer();
        }
        break;

    case ROTATE:
        if (block_can_rotate(active_block)) {
            undraw_block(active_block);
            active_block = block_rotate(active_block);
            draw_block(active_block);

            time_for_fall = set_fall_timer();
        }
        break;

    case DOWN:
        time_for_fall = 0;
        break;

    default:
        break;
    }

    // bool block_moved = false;
    // update_display(board);

    if (time_for_fall <= millis()) {
        // printf("%lld <= %lld\n", time_for_fall, millis());

        if (block_can_fall(active_block)) {
            undraw_block(active_block);

            current_block_down();

            draw_block(active_block);

            // block_moved = true;
        } else {
            // block cant move any more down,
            undraw_block(active_block);

            // add block to board
            for (int i = 0; i < 4; i++) {
                board[active_block.tiles[i].x][active_block.tiles[i].y] = active_block.type;
            }
            remove_full_lines();

            place_new_block();
            draw_block(active_block);

            // TODO: check if game over
            if (game_over()) {
                *sc = score;
                return false;
            }

            update_display(board);
        }

        time_for_fall = set_fall_timer();
    }

    return true;
}