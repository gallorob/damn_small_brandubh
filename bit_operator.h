#ifndef BIT_OPERATOR
#define BIT_OPERATOR

#include "constants.h"

/// <summary>Get the tile value</summary>
/// <param name="a">The byte</param> 
/// <param name="i">The bit index to read from</param> 
/// <param name="offset">Additional offset to read to (eg: i = 1, offset =1 -> read 2 bits)</param> 
/// <returns>The tile value</returns>
unsigned int tile_value(const char a, unsigned int i, unsigned int offset)
{
	return (a >> (game_variables.char_bit - (i + offset))) & (0x1 + offset);
}

unsigned int current_player(const unsigned char* game)
{
	return tile_value(game[ARR_LEN - 1], game_variables.player, 0x0);
}

/// <summary>Flip a single bit in a char</summary>
/// <param name="a">The byte</param> 
/// <param name="pos">The bit position</param> 
void flip_bit(unsigned char* a, unsigned int* pos)
{
	*a ^= (1 << *pos);
}

/// <summary>Get the tile at the specified (pair of) bit(s) of the character</summary>
/// <param name="board">The board</param> 
/// <param name="char_idx">The character index of the board</param> 
/// <param name="bit_idx">The bit index of the character</param> 
/// <returns>A tile</returns> 
unsigned int get_tile(const unsigned char *board, unsigned int* char_idx, const unsigned int* bit_idx)
{
	if (game_variables.debug)
	{
		printf("Called get_tile with Char-idx: 0x%x Bit-idx: 0x%x\n", *char_idx, *bit_idx);
	}
	unsigned int x = tile_value(board[*char_idx], *bit_idx, 0x2);
	if (game_variables.debug)
	{
		printf("\tRead: 0x%x\n", x);
	}
	return x;
}

/// <summary>Set the tile value</summary>
/// <param name="char_byte">The byte</param> 
/// <param name="tile_value">The new tile value</param> 
/// <param name="b_offset">Position in the byte (\in[1, 4])</param>
void set_tile(unsigned char* char_byte, const unsigned int* tile_value, const unsigned int* b_offset)
{
	if (game_variables.debug)
	{
		printf("Called set_tile with Char: 0x%x Tile value: 0x%x Position: 0x%x\n", *char_byte, *tile_value, *b_offset);
	}
	unsigned int delta = (*b_offset - 1) * 2;
	;
	*char_byte &= game_variables.full_byte & (~(0x3 << delta));
	*char_byte |= *tile_value << delta;
	if (game_variables.debug)
	{
		printf("\tExecuted set_tile: new Char: 0x%x Computed delta: 0x%x\n", *char_byte, delta);
	}
}

/// <summary>Get the tile at the specified [row, column] tuple</summary>
/// <param name="board">The board</param> 
/// <param name="y">The row (\in[0, BOARD_SIZE - 1])</param> 
/// <param name="x">The column (\in[0, BOARD_SIZE - 1])</param> 
/// <returns>The tile</returns> 
unsigned int get_board_at(const unsigned char* board, unsigned int* y, unsigned int* x)
{
	unsigned int value = (*y * game_variables.board_size) + *x;
	unsigned int char_idx = (value * 2) / game_variables.char_bit;
	const unsigned int bit_idx = (value * 2) % game_variables.char_bit;
	if (game_variables.debug)
	{
		printf("Called get_tile_by_pos with X: 0x%x Y: 0x%x\n\tComputed Value: 0x%x Char-idx: 0x%x Bit-idx: 0x%x\n", *x, *y, value, char_idx, bit_idx);
	}
	unsigned int t = get_tile(board, &char_idx, &bit_idx);
	if (game_variables.debug)
	{
		printf("\tRead: %u\n", t);
	}
	return t;
}

/// <summary>Set the tile at the specified [row, column] tuple</summary>
/// <param name="board">The board</param>
/// <param name="new_tile">The new tile</param>
/// <param name="y">The row (\in[0, BOARD_SIZE - 1])</param> 
/// <param name="x">The column (\in[0, BOARD_SIZE - 1])</param> 
/// <returns>The tile</returns> 
void set_board_at(unsigned char* board, const unsigned int* new_tile, const unsigned int* y, const unsigned int* x)
{
	unsigned int value = (*y * game_variables.board_size) + *x;
	unsigned int char_idx = (value * 2) / game_variables.char_bit;
	// note: t_idx considers position in the byte: 00 00 00 00 -> 4 3 2 1
	unsigned int t_idx = 0x4 - (((value * 2) % game_variables.char_bit) / 2);
	if (game_variables.debug)
	{
		printf("Called set_board_at with X: 0x%x Y: 0x%x\n\tComputed Value: 0x%x Char-idx: 0x%x Tile-idx: 0x%x Char: 0x%x\n", *x, *y, value, char_idx, t_idx, board[char_idx]);
	}
	set_tile(&(board[char_idx]), new_tile, &t_idx);
	if (game_variables.debug)
	{
		printf("\tSet char: 0x%x\n", board[char_idx]);
	}
}

#endif
