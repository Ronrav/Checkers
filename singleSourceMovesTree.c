#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "checkers_pos.h"

#define BOARD_SIZE 8

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef struct _SingleSourceMoveTreeNode {

	Board board;
	checkersPos* pos;
	unsigned short total_capture_so_far;
	struct SingleSourceMoveTreeNode* next_move[2];
}SingleSourceMovesTree;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTree* source;
}SingleSourceMovesTree;