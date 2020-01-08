#ifndef VISUALIZER
#define VISUALIZER

#include "constants.h"
#include "bit_operator.h"

/// <summary>Visualize the current game state</summary>
/// <param name="game">The current game</param>
void visualize_game(const char *game)
{
	// Tell who's playing
	printf("Current player is ");
	if (tile_value(game[game_variables.arr_len - 1], game_variables.player, 0x0) == 1)
	{
		printf("ATTACKER");
	}
	else
	{
		printf("DEFENDER");
	}
	printf(".\n");

	// Get the board representation
	printf("Current board:\n  A  B  C  D  E  F  G");
	for (int i = 0; i < game_variables.board_size; i++)
	{
		printf("\n%d", i + 1);
		for (int j = 0; j < game_variables.board_size; j++)
		{
			tile tile = board_at(game, &i, &j);
			switch (tile.data)
			{
			case T_DEF:
				printf(" D ");
				break;
			case T_KING:
				printf(" K ");
				break;
			case T_ATK:
				printf(" A ");
				break;
			case T_EMPTY:
				printf(" . ");
				break;
			default:
				break;
			}
		}
	}
	printf("\n");
}


#endif