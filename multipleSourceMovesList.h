#pragma once
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


MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);

void insertNodeToStartOfMultipleMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell * node);

MultipleSourceMovesListCell* createNewMovesListNode(SingleSourceMovesList* single_moves_list, MultipleSourceMovesListCell* next);

void insertDataToStartOfMultipleMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_list);

bool isMultipleMovesEmptyList(MultipleSourceMovesList* lst);

void freeMultipleMovesList(MultipleSourceMovesList* lst);

MultipleSourceMovesList* initDynamicMemMultipleMovesList();

void makeMultipleMovesEmptyList(MultipleSourceMovesList* lst);
