#ifndef CORE
#define CORE

#include "move.h"
#include "bit_operator.h"

void play_move(char* game)
{
	// read move
	const char* move = read_and_validate_move();
	// get tile FROM
	unsigned int x_f = col_to_num(&(move[0]));
	unsigned int y_f = row_to_num(&(move[1]));
	// get tile TO
	unsigned int x_t = col_to_num(&(move[3]));
	unsigned int y_t = row_to_num(&(move[4]));

	// get tile in FROM
	unsigned int piece_f = get_board_at(game, &y_f, &x_f);

	// get tile in TO
	unsigned int piece_t = get_board_at(game, &y_t, &x_t);

	// get current player
	unsigned int player = current_player(game);

	const unsigned int p_empty = T_EMPTY;

	// apply move
	if (piece_t == T_EMPTY)
	{
		if (piece_f == T_ATK && player == 1)
		{
			set_board_at(game, &piece_f, &y_t, &x_t);
			set_board_at(game, &p_empty, &y_f, &x_f);
		}
		else if ((piece_f == T_DEF || piece_f == T_KING) && player == 0)
		{
			set_board_at(game, &piece_f, &y_t, &x_t);
			set_board_at(game, &p_empty, &y_f, &x_f);
		}
	}

	// update player
	unsigned int player_pos = 0x5;
	flip_bit(&(game[ARR_LEN - 1]), &player_pos);
}

#endif
