#ifndef SINGLE_SOURCE_MOVES_TREE_H
#define SINGLE_SOURCE_MOVES_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "checkersPos.h"

#define EMPTY ' '
#define BOARD_SIZE 8
#define T_FIRST_IN_ROW BOARD_SIZE+'0'
#define T_LAST_IN_ROW '1'
#define T_LAST_IN_COL BOARD_SIZE+'A'
#define B_FIRST_IN_ROW '1'
#define B_LAST_IN_ROW BOARD_SIZE+'0'
#define B_LAST_IN_COL 'A'
#define NOT_FOUND (-1)
#define LEFT 0
#define RIGHT 1

typedef struct SingleSourceMoveTreeNode {

	Board board;
	checkersPos* pos;
	unsigned short total_capture_so_far;
	struct SingleSourceMoveTreeNode* next_move[2];
}SingleSourceMovesTreeNode;

typedef struct SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

//this function creates a tree of all the possible moves of a single checker
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);

SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos pos, bool* IsFirstStep, int* captures_counter);

bool hasCaptured(checkersPos curr, checkersPos new);

void fillNewBoard(Board src, checkersPos curr_pos, Board dest, checkersPos new_pos);

bool findRightMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step);

bool findLeftMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step);

bool findLeftMoveForTPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step);

bool findRightMoveForTPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step);

bool findRightMoveForBPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step);

bool findLeftMoveForBPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step);

SingleSourceMovesTreeNode* createNewTNODE(Board board, checkersPos pos, SingleSourceMovesTreeNode* leftp, SingleSourceMovesTreeNode* rightp);

void copyBoard(Board src, Board dest);

void helper(SingleSourceMovesTreeNode* r);

void printTree(SingleSourceMovesTree t);



#endif // !SINGLE_SOURCE_MOVES_TREE_H