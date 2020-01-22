#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "visualizer.h"

#include "bit_operator.h"

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
    
    // show an example of a move with tile setting
    unsigned int x = 5;
    unsigned int y = 3;
    unsigned int moved = 0x1;
    unsigned int t = T_EMPTY;
    printf("\nMove attacker from F4 to F7:\n");

    set_board_at(game, &t, &y, &x);
    y = 6;
    set_board_at(game, &moved, &y, &x);
    visualize_game(game);

    // todo: add everything else

    // for now, exit
    return 0;
}