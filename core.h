#ifndef CORE
#define CORE

#include "move.h"
#include "bit_operator.h"


/// <summary>Update player for the next turn</summary>
/// <param name="game">The game</param> 
void update_player(unsigned char* game)
{
	// update player
	unsigned int player_pos = 0x5;
	flip_bit(&(game[ARR_LEN - 1]), &player_pos);
}

/// <summary>Get the adjacent piece to the given position in the desired direction</summary>
/// <param name="game">The game</param>
/// <param name="x">The x position</param>
/// <param name="y">The y position</param>
/// <param name="dx">The x displacement (>0: right; <0: left)</param>
/// <param name="dy">The y displacement(>0: below; <0: above)</param>
/// <returns>The adjacent piece in the desired direction (=T_EMPTY if out of board's bounds)</returns> 
unsigned int get_adjacent_piece(unsigned char* game, const unsigned int* x, const unsigned int* y, unsigned int* dx, unsigned int* dy)
{
	unsigned int x1 = *x + *dx;
	unsigned int y1 = *y + *dy;
	unsigned int adj_piece = T_EMPTY;
	if (x1 <= game_variables.board_size && x1 >= 0 && y1 <= game_variables.board_size && y1 >= 0)
	{
		adj_piece = get_board_at(game, &y1, &x1);
	}
	return adj_piece;
}

unsigned int does_capture(unsigned char* game, const unsigned int* x, const unsigned int* y, unsigned int dx, unsigned int dy, unsigned int piece_type, unsigned int opp_piece)
{
	unsigned int adj_piece = get_adjacent_piece(game, x, y, &dx, &dy);
	if (adj_piece == opp_piece)
	{
		unsigned int next_x = *x + dx;
		unsigned int next_y = *y + dy;
		unsigned int next_p = get_adjacent_piece(game, &next_x, &next_y, &dx, &dy);
		return (next_p == piece_type);
	}
	return 0;
}

/// <summary>Apply captures</summary>
/// <param name="game">The game</param> 
/// <param name="moved_piece">The piece that has been moved</param> 
/// <param name="x">The destination's X</param> 
/// <param name="y">The destination's Y</param>
void apply_captures(unsigned char* game, unsigned int* moved_piece, unsigned int* x, unsigned int* y)
{
	if (*moved_piece == (unsigned int) T_KING)
	{
		return;
	}
	const unsigned int p_empty = T_EMPTY;
	switch (*moved_piece)
	{
	case T_ATK:
		// check above
		if (does_capture(game, x, y, 0, -1, T_ATK, T_DEF))
		{
			unsigned int y1 = *y - 1;
			set_board_at(game, &p_empty, &y1, x);
		}
		// check right
		if (does_capture(game, x, y, +1, 0, T_ATK, T_DEF))
		{
			unsigned int x1 = *x + 1;
			set_board_at(game, &p_empty, y, &x1);
		}
		// check left
		if (does_capture(game, x, y, -1, 0, T_ATK, T_DEF))
		{
			unsigned int x1 = *x - 1;
			set_board_at(game, &p_empty, y, &x1);
		}
		// check below
		if (does_capture(game, x, y, 0, +1, T_ATK, T_DEF))
		{
			unsigned int y1 = *y + 1;
			set_board_at(game, &p_empty, &y1, x);
		}
		break;
	
	default:
		break;
	}
}

unsigned int play_move(unsigned char* game)
{
	const unsigned int p_empty = T_EMPTY;
	unsigned int x_f;
	unsigned int y_f;
	unsigned int x_t;
	unsigned int y_t;
	unsigned int piece_f;
	unsigned int piece_t;
	unsigned int valid = 0; // +1 for invalid piece, +1 for invalid destination
	// move reading cycle
	do
	{
		printf("Enter your move: ");
		// reset valid
		valid = 0;
		// read move
		const char* move = read_and_validate_move();
		// get tile FROM
		x_f = col_to_num(&(move[0]));
		y_f = row_to_num(&(move[1]));
		// get tile TO
		x_t = col_to_num(&(move[3]));
		y_t = row_to_num(&(move[4]));

		// get tile in FROM
		piece_f = get_board_at(game, &y_f, &x_f);

		// get tile in TO
		piece_t = get_board_at(game, &y_t, &x_t);

		// get current player
		unsigned int player = current_player(game);

		if ((piece_f == T_ATK && player == (unsigned int) 0) || ((piece_f == T_DEF || piece_f == T_KING) && player == 1))
		{
			valid++;
			printf("[Error]: Moving piece is an opponent's piece.\n");
		}
		if (piece_t != p_empty)
		{
			valid++;
			printf("[Error]: Destination tile is already occupied by a piece.\n");
		}
	} while (valid != 0);

	// apply move
	set_board_at(game, &piece_f, &y_t, &x_t);
	set_board_at(game, &p_empty, &y_f, &x_f);

	apply_captures(game, &piece_f, &x_t, &y_t);

	update_player(game);

	return piece_f;
}

#endif
