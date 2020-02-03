#ifndef CONSTANTS
#define CONSTANTS

// tile types
#define T_EMPTY 0x0	// Empty tile:		00
#define T_ATK 0x1	// Attacker tile:	01
#define T_DEF 0x2	// Defender tile:	10
#define T_KING 0x3	// King tile:		11
// (BOARD_SIZE * BOARD_SIZE * 0x2 / CHAR_BIT) + 1 = 13 bytes, 104 bits (98 used for board, 6 extra)
#define ARR_LEN 13
#define MOVE_LEN 5

typedef struct {
	// type bit dimensions
	unsigned int char_bit : 4;
	// board dimension (n x n)
	unsigned int board_size : 3;
	// current player:	last char: 0010 0000
	unsigned int player : 2;
	unsigned int debug : 1;
	unsigned int full_byte : 8;
} variables;

variables game_variables = { \
	.char_bit = 0x8, \
	.board_size = 0x7, \
	.player = 0x3, \
	.debug = 0x0,  \
	.full_byte = 0xff
};

/// <summary>Set up the default Brandubh board</summary>
/// <param name="board">The board</param>
void setup_default_brandubh_board(unsigned char *board)
{
	/*
	. . . A		0000 0001	0x1
	. . . .		0000 0000	0x0
	. . A .		0000 0100	0x4
	. . . .		0000 0000	0x0
	. D . .		0010 0000	0x20
	. A A D		0001 0110	0x16
	K D A A		1110 0101	0xE5
	. . . D		0000 0010	0x2
	. . . .		0000 0000	0x0
	. . A .		0000 0100	0x4
	. . . .		0000 0000	0x0
	. A . .		0001 0000	0x10
	.			00			0x0
	*/
	unsigned int tiles[13] = { 0x1, 0x0, 0x4, 0x0, 0x20, 0x16, 0xE5, 0x2, 0x0, 0x4, 0x0, 0x10, 0x0 };
	// this is a lazy approach; a more efficient one would be to initialize the game with this board already
	// todo: make the change once everything else works
	for (int i = 0; i < 13; i++)
	{
		board[i] = tiles[i];
	}
}

#endif