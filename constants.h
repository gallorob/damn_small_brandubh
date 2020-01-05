#ifndef CONSTANTS
#define CONSTANTS

#include <climits>

// board infos
#define BOARD_SIZE 0x7	// board dimension (n x n)
#define ARR_LEN (int)(BOARD_SIZE * BOARD_SIZE * 0x2 / CHAR_BIT) + 1	// = 13 bytes, 104 bits (98 used for board, 6 extra)
// tile types
#define T_EMPTY 0x0	// Empty tile:		00
#define T_ATK 0x1	// Attacker tile:	01
#define T_DEF 0x2	// Defender tile:	10
#define T_KING 0x3	// King tile:		11
// extra info
#define PLAYER 0x20	// current player:	0010 0000
#define DEBUG 0x0

// use a struct with a bitfield of 2 bits since we know all possible values are in [0,3]
// note: sizeof(tile) = 4 (bytes) but it should only use 2 (go figure)
typedef struct tile {
	unsigned int data : 2;
} tile;

/// <summary>Set up the default Brandubh board</summary>
/// <param name="board">The board</param>
void setup_default_brandubh_board(char *board)
{
	/*
	. . . A		0000 0001	0x1
	. . . .		0000 0000	0x0
	. . A .		0000 0100	0x4
	. . . .		0000 0000	0x0
	. D . .		0010 0000	0x20
	. A A D		0001 0110	0x16
	K D D A		1110 1001	0xE9
	. . . D		0000 0010	0x2
	. . . .		0000 0000	0x0
	. . A .		0000 0100	0x4
	. . . .		0000 0000	0x0
	. A . .		0001 0000	0x10
	.			00			0x0
	*/
	unsigned int tiles[13] = { 0x1, 0x0, 0x4, 0x0, 0x20, 0x16, 0xE9, 0x2, 0x0, 0x4, 0x0, 0x10, 0x0 };
	// this is a lazy approach; a more efficient one would be to initialize the game with this board already
	// todo: make the change once everything else works
	for (int i = 0; i < 13; i++)
	{
		board[i] = tiles[i];
	}
}

#endif