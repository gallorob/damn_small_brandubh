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

/// <summary>Get the tile at the specified (pair of) bit(s) of the character</summary>
/// <param name="board">The board</param> 
/// <param name="char_idx">The character index of the board</param> 
/// <param name="bit_idx">The bit index of the character</param> 
/// <returns>A tile</returns> 
tile get_tile(const char *board, int* char_idx, int* bit_idx)
{
	if (game_variables.debug)
	{
		printf("Called get_tile with Char-idx: %u Bit-idx: %u\tRead: %u\n", *char_idx, *bit_idx, tile_value(board[*char_idx], *bit_idx, 0x0));
	}
	return (tile) { .data = tile_value(board[*char_idx], *bit_idx, 0x2) };	
}

/// <summary>Get the tile at the specified [row, column] tuple</summary>
/// <param name="board">The board</param> 
/// <param name="x">The row (\in[0, BOARD_SIZE])</param> 
/// <param name="y">The column (\in[0, BOARD_SIZE])</param> 
/// <returns>The tile</returns> 
tile board_at(const char* board, int* x, int* y)
{
	unsigned int value = (*x * game_variables.board_size) + *y;
	unsigned int char_idx = (value * 2) / game_variables.char_bit;
	unsigned int bit_idx = (value * 2) % game_variables.char_bit;
	if (game_variables.debug)
	{
		printf("Called get_tile_by_pos with X: %u Y: %u\tComputed Value: %2u Char-idx: %u Bit-idx: %u\tRead: %u\n", *x, *y, value, char_idx, bit_idx, get_tile(board, &char_idx, &bit_idx).data);
	}
	return get_tile(board, &char_idx, &bit_idx);
}

#endif
