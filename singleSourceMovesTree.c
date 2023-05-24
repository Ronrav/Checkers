#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "checkersPos.h"
#include "board.h"


typedef struct _SingleSourceMoveTreeNode {

	Board board;
	checkersPos* pos;
	unsigned short total_capture_so_far;
	struct SingleSourceMoveTreeNode* next_move[2];
}SingleSourceMovesTree;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTree* source;
}SingleSourceMovesTree;