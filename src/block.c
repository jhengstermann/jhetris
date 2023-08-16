
#include "block.h"

#include <stdlib.h>

block new_block() {
    int rand_type = (rand() % 7) + 1;

    // int rand_type = 1; // L
    // int rand_type = 2; // J
    // int rand_type = 3; // I
    // int rand_type = 4; // T
    // int rand_type = 5; // S
    // int rand_type = 6; // Z
    // int rand_type = 7; // O

    block new;
    new.type     = (block_type)rand_type;
    new.rotation = DEG_0;

    new.center_coordinate.x = 0;
    new.center_coordinate.y = 0;

    switch (new.type) {
    case L_BLOCK:
        new.tiles[0].x = 0;
        new.tiles[0].y = -1;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = 0;
        new.tiles[2].y = 1;

        new.tiles[3].x = 1;
        new.tiles[3].y = 1;
        break;

    case J_BLOCK:
        new.tiles[0].x = 0;
        new.tiles[0].y = -1;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = 0;
        new.tiles[2].y = 1;

        new.tiles[3].x = -1;
        new.tiles[3].y = 1;
        break;

    case I_BLOCK:
        new.tiles[0].x = 0;
        new.tiles[0].y = -1;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = 0;
        new.tiles[2].y = 1;

        new.tiles[3].x = 0;
        new.tiles[3].y = 2;
        break;

    case T_BLOCK:
        new.tiles[0].x = -1;
        new.tiles[0].y = 0;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = 1;
        new.tiles[2].y = 0;

        new.tiles[3].x = 0;
        new.tiles[3].y = 1;
        break;

    case S_BLOCK:
        new.tiles[0].x = -1;
        new.tiles[0].y = 0;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = 0;
        new.tiles[2].y = -1;

        new.tiles[3].x = 1;
        new.tiles[3].y = -1;
        break;

    case Z_BLOCK:
        new.tiles[0].x = 1;
        new.tiles[0].y = 0;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = 0;
        new.tiles[2].y = -1;

        new.tiles[3].x = -1;
        new.tiles[3].y = -1;
        break;

    case O_BLOCK:
        new.tiles[0].x = -1;
        new.tiles[0].y = 0;

        new.tiles[1].x = 0;
        new.tiles[1].y = 0;

        new.tiles[2].x = -1;
        new.tiles[2].y = -1;

        new.tiles[3].x = 0;
        new.tiles[3].y = -1;
        break;

    default:
        break;
    }

    return new;
}

block rotate_L(block b);
block rotate_J(block b);
block rotate_I(block b);
block rotate_T(block b);
block rotate_S(block b);
block rotate_Z(block b);
block rotate_O(block b);

block block_rotate(block b) {
    block r;

    switch (b.type) {
    case L_BLOCK:
        r = rotate_L(b);
        break;

    case J_BLOCK:
        r = rotate_J(b);
        break;

    case I_BLOCK:
        r = rotate_I(b);
        break;

    case T_BLOCK:
        r = rotate_T(b);
        break;

    case S_BLOCK:
        r = rotate_S(b);
        break;

    case Z_BLOCK:
        r = rotate_Z(b);
        break;

    case O_BLOCK:
        r = rotate_O(b);
        break;

    default:
        break;
    }

    return r;
};

/* ----------------------------------------------------------------------- */

block rotate_Z(block b) {
    switch (b.rotation) {
    case DEG_0:
        b.tiles[2].y += 2;

        b.tiles[3].x += 2;

        b.rotation = DEG_90;
        break;

    case DEG_90:
        b.tiles[2].y -= 2;

        b.tiles[3].x -= 2;

        b.rotation = DEG_0;
        break;

    default:
        break;
    }

    return b;
}

block rotate_S(block b) {
    switch (b.rotation) {
    case DEG_0:
        b.tiles[2].y += 2;

        b.tiles[3].x -= 2;

        b.rotation = DEG_90;
        break;

    case DEG_90:
        b.tiles[2].y -= 2;

        b.tiles[3].x += 2;

        b.rotation = DEG_0;
        break;

    default:
        break;
    }

    return b;
}

block rotate_T(block b) {
    switch (b.rotation) {
    case DEG_0:
        b.tiles[2].x -= 1;
        b.tiles[2].y -= 1;

        b.rotation = DEG_90;
        break;

    case DEG_90:
        b.tiles[3].x += 1;
        b.tiles[3].y -= 1;

        b.rotation = DEG_180;
        break;

    case DEG_180:
        b.tiles[0].x += 1;
        b.tiles[0].y += 1;

        b.rotation = DEG_270;
        break;

    case DEG_270:
        b.tiles[0].x -= 1;
        b.tiles[0].y -= 1;

        b.tiles[2].x += 1;
        b.tiles[2].y += 1;

        b.tiles[3].x -= 1;
        b.tiles[3].y += 1;

        b.rotation = DEG_0;
        break;

    default:
        break;
    }

    return b;
}

block rotate_O(block b) {
    return b;
}

block rotate_I(block b) {
    switch (b.rotation) {
    case DEG_0:
        b.tiles[0].x -= 1;
        b.tiles[0].y += 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x += 1;
        b.tiles[2].y -= 1;

        b.tiles[3].x += 2;
        b.tiles[3].y -= 2;

        b.rotation = DEG_90;
        break;

    case DEG_90:
        b.tiles[0].x += 1;
        b.tiles[0].y -= 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x -= 1;
        b.tiles[2].y += 1;

        b.tiles[3].x -= 2;
        b.tiles[3].y += 2;

        b.rotation = DEG_0;
        break;

    default:
        break;
    }

    return b;
}

block rotate_J(block b) {
    switch (b.rotation) {
    case DEG_0:
        b.tiles[0].x += 1;
        b.tiles[0].y += 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x -= 1;
        b.tiles[2].y -= 1;

        b.tiles[3].x += 0;
        b.tiles[3].y -= 2;

        b.rotation = DEG_90;
        break;

    case DEG_90:
        b.tiles[0].x -= 1;
        b.tiles[0].y += 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x += 1;
        b.tiles[2].y -= 1;

        b.tiles[3].x += 2;
        // b.tiles[3].y += 0;

        b.rotation = DEG_180;
        break;

    case DEG_180:
        b.tiles[0].x -= 1;
        b.tiles[0].y -= 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x += 1;
        b.tiles[2].y += 1;

        // b.tiles[3].x += 0;
        b.tiles[3].y += 2;

        b.rotation = DEG_270;
        break;

    case DEG_270:
        b.tiles[0].x += 1;
        b.tiles[0].y -= 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x -= 1;
        b.tiles[2].y += 1;

        b.tiles[3].x -= 2;
        // b.tiles[3].y += 0;

        b.rotation = DEG_0;
        break;

    default:
        break;
    }

    return b;
}

block rotate_L(block b) {
    switch (b.rotation) {
    case DEG_0:
        b.tiles[0].x += 1;
        b.tiles[0].y += 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x -= 1;
        b.tiles[2].y -= 1;

        b.tiles[3].x -= 2;
        // b.tiles[3].y += 0;

        b.rotation = DEG_90;
        break;

    case DEG_90:
        b.tiles[0].x -= 1;
        b.tiles[0].y += 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x += 1;
        b.tiles[2].y -= 1;

        // b.tiles[3].x += 0;
        b.tiles[3].y -= 2;

        b.rotation = DEG_180;
        break;

    case DEG_180:
        b.tiles[0].x -= 1;
        b.tiles[0].y -= 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x += 1;
        b.tiles[2].y += 1;

        b.tiles[3].x += 2;
        // b.tiles[3].y += 0;

        b.rotation = DEG_270;
        break;

    case DEG_270:
        b.tiles[0].x += 1;
        b.tiles[0].y -= 1;

        // b.tiles[1].x += 0;
        // b.tiles[1].y += 0;

        b.tiles[2].x -= 1;
        b.tiles[2].y += 1;

        // b.tiles[3].x += 0;
        b.tiles[3].y += 2;

        b.rotation = DEG_0;
        break;

    default:
        break;
    }

    return b;
}