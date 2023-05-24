#ifndef SINGLE_SOURCE_MOVES_TREE_H
#define SINGLE_SOURCE_MOVES_TREE_H

#include "board.h"
typedef struct _SingleSourceMoveTreeNode {

	Board board;
	checkersPos* pos;
	unsigned short total_capture_so_far;
	struct SingleSourceMoveTreeNode* next_move[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree 
{
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

#endif // !SINGLE_SOURCE_MOVES_TREE_H