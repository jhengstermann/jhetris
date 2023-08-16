
#ifndef BLOCK_H
#define BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int x;
    int y;
} position;

typedef enum {
    EMPTY_TILE = 0,
    L_BLOCK,
    J_BLOCK,
    I_BLOCK,
    T_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    O_BLOCK
} block_type;

typedef enum {
    DEG_0 = 0,
    DEG_90,
    DEG_180,
    DEG_270
} degree_t;

typedef struct {
    block_type type;
    position tiles[4];
    position center_coordinate;
    degree_t rotation;
} block;

block new_block();
block block_rotate(block b);

#ifdef __cplusplus
}
#endif

#endif /* BLOCK_H */