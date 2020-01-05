#ifndef BIT_OPERATOR
#define BIT_OPERATOR

#include <climits>
#include "constants.h"

//#define bit_at(a,i) !!(a[i / CHAR_BIT] >> (CHAR_BIT - (i % CHAR_BIT) - 1) & 1)
#define bit_at(a,i) !!(a >> (CHAR_BIT - (i % CHAR_BIT) - 1) & 1)

tile get_tile_single_char(const char c, int* char_idx, int* bit_idx)
{
	tile result;
	result.piece = bit_at(c, *bit_idx);
	result.colour = bit_at(c, *bit_idx + 1);
	result.king = bit_at(c, *bit_idx + 2);
	*bit_idx += 3;
	return result;
}

tile get_tile_multiple_chars(const char c1, const char c2, int* char_idx, int* bit_idx)
{
	tile result;
	if (*bit_idx == 6)
	{
		result.piece = bit_at(c1, *bit_idx);
		result.colour = bit_at(c2, *bit_idx + 1);
		result.king = bit_at(c2, 0);
		*bit_idx = 1;
	}
	else
	{
		result.piece = bit_at(c1, *bit_idx);
		result.colour = bit_at(c2, 0);
		result.king = bit_at(c2, 1);
		*bit_idx = 2;
	}
	*char_idx += 1;
	return result;
}

tile get_tile(const char *board, int* char_idx, int* bit_idx)
{
	if (*bit_idx < 6)
	{
		return get_tile_single_char(board[*char_idx], char_idx, bit_idx);
	}
	else
	{
		return get_tile_multiple_chars(board[*char_idx], board[*char_idx + 1], char_idx, bit_idx);
	}
}

#endif
