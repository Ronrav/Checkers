#ifndef SINGLE_SOURCE_LIST_H
#define SINGLE_SOURCE_LIST_H

#include "board.h"
#include "checkersPos.h"
#include "singleSourceMovesTree.h"

#define NULL_TREE (-1)
#define LEFT 0
#define RIGHT 1

typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;

}SingleSourceMovesList;

/*This function receives the possible moves tree and creates a SingleSourceMovesList object
containing the optimal move of a player from a certain position*/
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);

/*this function inits a new SingleSourceMovesList list*/
SingleSourceMovesList* initDynamicMemList();
/*This function makes a SingleSourceMovesList empty*/
void makeEmptyList(SingleSourceMovesList* lst);

/*This is a helper function for "FindSingleSourceOptimalMove"*/
void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, SingleSourceMovesList* lst, int max_captures, bool* flag);

/*This function inserts a new node to the start of SingleSourceMovesList*/
void insertNodeToStartOfMovesList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node);

/*This function creates a new SingleSourceMovesList node*/
SingleSourceMovesListCell* createNewMovesListNode(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);

/*This function inserts a new data (checkers position and captures)to the start of SingleSourceMovesList*/
void insertDataToStartOfMovesList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures);

/*This function checks if a list is empty*/
bool isEmptyList(SingleSourceMovesList* lst);

/*This function free's the memory of a SingleSourceMovesList*/
void freeMovesList(SingleSourceMovesList* lst);

/*This function free's the memory of a SingleSourceMovesList node*/
void freeMovesListNode(SingleSourceMovesListCell* node);

/*This is a helper function of "getMaxCaptures"*/
void getMaxCapturesHelper(SingleSourceMovesTreeNode* source, int* max);

/*This function finds and returns the highest number of captures in the moves_tree*/
int getMaxCaptures(SingleSourceMovesTree* moves_tree);

#endif // !SINGLE_SOURCE_LIST_H