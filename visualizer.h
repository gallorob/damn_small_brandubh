#ifndef VISUALIZER
#define VISUALIZER

#include "constants.h"
#include "bit_operator.h"

#include "core.h"

/// <summary>Visualize the current game state</summary>
/// <param name="game">The current game</param>
void visualize_game(const unsigned char *game)
{
	// Tell who's playing
	printf("Current player is ");
	if (current_player(game) == (unsigned int) 1)
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
	for (unsigned int i = 0; i < game_variables.board_size; i++)
	{
		printf("\n%d", i + 1);
		for (unsigned int j = 0; j < game_variables.board_size; j++)
		{
			unsigned int tile = get_board_at(game, &i, &j);
			switch (tile)
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
				if (is_corner(&i, &j) || is_throne(&i, &j))
				{
					printf(" x ");
				}
				else
				{
					printf(" . ");
				}
				break;
			default:
				break;
			}
		}
	}
	printf("\n");
}


#endif