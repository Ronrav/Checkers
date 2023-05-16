#include "checkers_pos.h"
#include "singleSourceMovesTree.h"
#define NULL_TREE -1
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

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);

SingleSourceMovesList* initDynamicMemList();

void makeEmptyList(SingleSourceMovesList* lst);

void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, SingleSourceMovesList* lst, int depth, bool flag);

int getTreeDepth(SingleSourceMovesTree* moves_tree);

int getTreeDepthHelper(SingleSourceMovesTreeNode* source);

void insertNodeToStartOfMovesList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node);

SingleSourceMovesListCell* createNewMovesListNode(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);

void insertDataToStartOfMovesList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures);

bool isEmptyList(SingleSourceMovesList* lst);

int getMax(int a, int b);
