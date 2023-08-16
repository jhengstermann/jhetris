
#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "global_macros.h"

#include "block.h"

typedef enum {
    NO_INPUT,
    LEFT,
    RIGHT,
    ROTATE,
    DOWN
} input_t;

void new_game();

bool board_update(input_t control, int *sc);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */