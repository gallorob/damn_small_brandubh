#ifndef VISUALIZER
#define VISUALIZER

#include "constants.h"
#include "bit_operator.h"

void visualize_game(const char *game)
{
	// Tell who's playing
	printf("Current player is ");
	if ((game[ARR_LEN - 1] & PLAYER_MASK) == PLAYER_MASK)
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
	int char_idx = 0;
	int bit_idx = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		printf("\n%d", i + 1);
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			tile tile = get_tile(game, &char_idx, &bit_idx);
			if (tile.piece)
			{
				if (tile.colour)
				{
					if (tile.king)
					{
						printf(" K ");
					}
					else
					{
						printf(" D ");
					}
				}
				else
				{
					printf(" A ");
				}
			}
			else
			{
				printf(" . ");
			}
		}
	}
	printf("\n");
}



#endif