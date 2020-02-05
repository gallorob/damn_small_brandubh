#ifndef MOVE
#define MOVE

#include <stdio.h>

#include "constants.h"

/// <summary>Check if a move is valid (format a1-b2)</summary>
/// <param name="move">The move</param>
/// <returns>0 if the move is valid, -1 otherwise</returns> 
int validate_move(const char *move)
{
	// quick and dirty way to get length of move string
	unsigned int i = 0;
	while (move[++i]);
	// actual check
	if (i - 1 < 5)  // -1 is for \0 termination
	{
		if (move[0] >= 'a' && move[0] <= 'z' && \
			move[1] > '0' && move[1] < '8' && \
			move[2] == '-' && \
			move[3] >= 'a' && move[3] <= 'z' && \
			move[4] > '0' && move[4] < '8')
		{
			return 0;
		}
	}
	return -1;
}

/// <summary>Remove possible capital letters in the move</summary>
/// <param name="move">The move</param>
void remove_capital(char* move)
{
	if (move[0] >= 65 && move[0] <= 90)
	{
		move[0] += 32;
	}
	if (move[3] >= 65 && move[3] <= 90)
	{
		move[3] += 32;
	}
}

/// <summary>Get the column's indexable number</summary>
/// <param name="col">The column</param>
/// <returns>The column's number</returns> 
int col_to_num(const char* col)
{
	return *col - 'a';
}

/// <summary>Get the row's indexable number</summary>
/// <param name="row">The row</param>
/// <returns>The row's number</returns> 
int row_to_num(const char* row)
{
	return *row - '0' - 1;
}

/// <summary>Read and validate a move from stdin</summary>
/// <returns>A valid move</returns> 
const char* read_and_validate_move()
{
	static char input[MOVE_LEN + 1];
	int x = -1;
	while (x < 0)
	{
		fgets(input, MOVE_LEN + 1, stdin);
		remove_capital(input);
		x = validate_move(input);
		fseek(stdin, 0, SEEK_END);
	}
	return input;
}

#endif