#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "visualizer.h"


// 152 usable bits, divided in:
// bits 151 to 4:   board (3x7x7 bits necessary)
// bit 3:           current player
// bits 2 to 0:     extra
unsigned char board[ARR_LEN] = { '\0' };

int main() {
    board[ARR_LEN - 1] = 0x8;
    board[0] |= 0xF3;
    visualize_game(board);
    printf("\nDeclared size of game: %d bytes.\n", (int)sizeof(board));

    return 0;
}