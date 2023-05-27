#ifndef SINGLE_SOURCE_MOVES_TREE_H
#define SINGLE_SOURCE_MOVES_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "checkersPos.h"  

#define NULL_TREE (-1)
#define BOARD_SIZE 8
#define T_FIRST_IN_ROW BOARD_SIZE+'0'
#define T_LAST_IN_ROW '1'
#define T_LAST_IN_COL BOARD_SIZE+'A'
#define B_FIRST_IN_ROW '1'
#define B_LAST_IN_ROW BOARD_SIZE+'0'
#define B_LAST_IN_COL 'A'
#define NOT_FOUND 0
#define LEFT 0
#define RIGHT 1
# define T_NEXT_ROW 1
#define B_NEXT_ROW (-1)
#define T_COL_FROM_RIGHT (-1)
#define T_COL_FROM_LEFT 1
#define B_COL_FROM_RIGHT 1
#define B_COL_FROM_LEFT (-1)



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

SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos pos, bool IsFirstStep, int* captures_counter);

bool hasCaptured(checkersPos curr, checkersPos new);

void fillNewBoard(Board src, checkersPos curr_pos, Board dest, checkersPos new_pos);

bool pIsRightMost(Board board, checkersPos pos, char player);

bool pIsLeftMost(Board board, checkersPos pos, char player);

bool Is2StepsAvailable(Board board, checkersPos pos, char p, int side, int next_row);

bool isOneStepAvailble(Board board, checkersPos pos, int side, int next_row);

bool findNextMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step, char p, int side, int next_row);

void initVariablesToPlayer(int p, int* right, int* left, int* next_row);

void findPossibleMoves(Board board, checkersPos pos, checkersPos* right_new_pos, checkersPos* left_new_pos, bool is_first_step, bool* is_right_possible, bool* is_left_possible);

void printTree(SingleSourceMovesTree t);
void helper(SingleSourceMovesTreeNode* r);
SingleSourceMovesTreeNode* createNewTNODE(Board board, checkersPos pos, SingleSourceMovesTreeNode* leftp, SingleSourceMovesTreeNode* rightp, int capture_counter);

void copyBoard(Board src, Board dest);

void freeTree(SingleSourceMovesTree* tree);

void freeTreeHelper(SingleSourceMovesTreeNode* source);


#endif // !SINGLE_SOURCE_MOVES_TREE_H