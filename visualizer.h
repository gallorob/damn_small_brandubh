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
	if ((game[ARR_LEN - 1] & PLAYER) == PLAYER)
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
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		printf("\n%d", i + 1);
		for (int j = 0; j < BOARD_SIZE; j++)
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