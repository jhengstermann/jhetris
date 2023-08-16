
#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "global_macros.h"

#include "block.h"

void clear_display();

void update_display(block_type board[BOARD_WIDTH][BOARD_HEIGHT]);

void draw_block(block b);
void undraw_block(block b);


#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_H */