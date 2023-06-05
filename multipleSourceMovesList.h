#ifndef MULTIPLE_SOURCE_MOVES_LIST_H
#define MULTIPLE_SOURCE_MOVES_LIST_H

#include "board.h"
#include "singleSourceList.h"

typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
}MultipleSourceMovesList;

/*This function creates a MultipleSourceMovesList which holds
a SingleSourceMovesList representign the best move of each of the player's pieces*/
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);

/*This function inserts a MultipleSourceMovesListCell to the start of MultipleSourceMovesList*/
void insertNodeToStartOfMultipleMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell * node);

/*This function creates a new MultipleSourceMovesListCell*/
MultipleSourceMovesListCell* createNewMultipleMovesListNode(SingleSourceMovesList* single_moves_list, MultipleSourceMovesListCell* next);

/*This function inserts a SingleSourceMovesList to the start of MultipleSourceMovesList*/
void insertDataToStartOfMultipleMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_list);

/*This function check if a MultipleSourceMovesList is empty*/
bool isMultipleMovesEmptyList(MultipleSourceMovesList* lst);

/*This function free's the memory of a dynamic multiple moves list */
void freeMultipleMovesList(MultipleSourceMovesList* lst);

/*This function inits a new MultipleSourceMovesList which includes
allocating dynamic memory and setting NULL values (emptying the list)*/
MultipleSourceMovesList* initDynamicMemMultipleMovesList();

/*This function makes a MultipleSourceMovesList empty*/
void makeMultipleMovesEmptyList(MultipleSourceMovesList* lst);

/*this function checks if a single source list contains only 1 node*/
bool isPossibleMove(SingleSourceMovesList lst);

/*This function inserts new SingleSourceMovesList to the end of MultipleSourceMovesList*/
void insertDataToEndOfMultipleMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_list);

/*This function inserts a new node to the end of the list*/
void insertNodeToEndOfMultipleMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node);

/*This function inserts new data to a players multiple moves list*/
void insertDataToPlayersPlaceInList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_lst, Player player);

#endif // !MULTIPLE_SOURCE_MOVES_LIST_H