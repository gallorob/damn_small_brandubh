#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "visualizer.h"

// The game state
unsigned char game[ARR_LEN] = { '\0' };

int main() {
    // setup the game
    setup_default_brandubh_board(game);
    game[ARR_LEN - 1] |= 0x20;
    // visualize the game state
    visualize_game(game);
    // admire how little memory it takes
    printf("\nSize of game state: %d bytes.\n", (int)sizeof(game));
    printf("Size of constants: %d bytes.\n", (int)sizeof(game_variables));

    // todo: add everything else

    // for now, exit
    return 0;
}