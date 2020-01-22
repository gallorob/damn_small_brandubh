#ifndef MOVE
#define MOVE

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
			move[0] >= 'a' && move[0] <= 'z' && \
			move[1] > '0' && move[1] < '8')
		{
			return 0;
		}
	}
	return -1;
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
int row_to_num(const int* row)
{
	return *row - 1;
}

#endif