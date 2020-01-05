#ifndef CONSTANTS
#define CONSTANTS

#define BOARD_SIZE 0x7
#define TILE_MASK 0x7
#define PIECE_MASK 0x4
#define COLOUR_MASK 0x2
#define KING_MASK 0x1
#define PLAYER_MASK 0x8
#define ARR_LEN (int)(BOARD_SIZE * BOARD_SIZE * 0x3 / 8) + 1

typedef struct {
    unsigned int piece : 1;  // 1 if piece, 0 if NULL
    unsigned int colour : 1; // 1 if white, 0 if black
    unsigned int king : 1;   // 1 if king, 0 otherwise
} tile;


#endif