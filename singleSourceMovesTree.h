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

/* 
	Allocatesand returns a SingleSourceMovesTree for a specified checker on a game board.
	Returns NULL if the position is empty or memory allocation fails.
*/
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);

/*
	Constructs a tree of all possible moves for a checker at a specified position.
*/
SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos pos, bool IsFirstStep, unsigned short* captures_counter);

/*
	Determines whether a move between two positions involves capturing an opponent's checker.
*/
bool hasCaptured(checkersPos curr, checkersPos new);

/*
	Generates a new game board based on a move from one position to another.
*/
void fillNewBoard(Board src, checkersPos curr_pos, Board dest, checkersPos new_pos);

/*
	Determines if a checker is at the rightmost position.
	*/

bool pIsRightMost(Board board, checkersPos pos, Player player);

/*
	Determines if a checker is at the leftmost position.
*/
bool pIsLeftMost(Board board, checkersPos pos, Player player);

/*
	Checks if a two-step move is available for a checker.
*/
bool Is2StepsAvailable(Board board, checkersPos pos, Player p, int side, int next_row);

/*
	Checks if a single-step move is available for a checker.
*/
bool isOneStepAvailble(Board board, checkersPos pos, int side, int next_row);

/*
	Finds the next possible move for a checker at a specified position.
*/
bool findNextMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step, Player p, int side, int next_row);

/*
	Sets the direction of movement based on the player's checker.
*/
void initVariablesToPlayer(Player p, int* right, int* left, int* next_row);

/*
	Determines all possible moves for a checker at a specified position.
*/
void findPossibleMoves(Board board, checkersPos pos, checkersPos* right_new_pos, checkersPos* left_new_pos, bool is_first_step, bool* is_right_possible, bool* is_left_possible);

/*
	Allocates and returns a new tree node for a specified checker's move.
*/
SingleSourceMovesTreeNode* createNewTNODE(Board board, checkersPos pos, SingleSourceMovesTreeNode* leftp, SingleSourceMovesTreeNode* rightp, unsigned short capture_counter);

/*
	Copies the state of one game board to another.
*/
void copyBoard(Board src, Board dest);

/*
	Deallocates a tree representing all possible moves for a checker.
*/
void freeTree(SingleSourceMovesTree* tree);

/*
	Recursively deallocates the tree of possible moves.
*/
void freeTreeHelper(SingleSourceMovesTreeNode* source);


#endif // !SINGLE_SOURCE_MOVES_TREE_H