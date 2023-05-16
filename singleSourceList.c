#include "singleSourceList.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	int depth = getTreeDepth(moves_tree);
	SingleSourceMovesList* lst = initDynamicMemList();
	bool found_left = false, found_right = false;
	FindSingleSourceOptimalMoveHelper(moves_tree->source, lst, depth, found_left);
}

void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, SingleSourceMovesList* lst, int depth, bool* flag)
{
	if (source == NULL)
		return;
	if (depth == 0)
	{
		insertDataToStartOfMovesList(lst, source->pos, source->total_capture_so_far);
		*flag = true;
		return;
	}
	FindSingleSourceOptimalMoveHelper(source->next_move[LEFT], lst, depth - 1, flag);
	if (*flag)
	{
		insertDataToStartOfMovesList(lst, source->pos, source->total_capture_so_far);
		return;
	}
	FindSingleSourceOptimalMoveHelper(source->next_move[RIGHT], lst, depth - 1, flag);
	if (*flag)
		insertDataToStartOfMovesList(lst, source->pos, source->total_capture_so_far);	
}

SingleSourceMovesList* initDynamicMemList()
{
	SingleSourceMovesList* lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	if (lst == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	makeEmptyList(lst);
	return lst;
}

void makeEmptyList(SingleSourceMovesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

int getTreeDepth(SingleSourceMovesTree* moves_tree)
{
	if (moves_tree->source == NULL)
		return NULL_TREE;
	return getTreeDepthHelper(moves_tree->source);
}

int getTreeDepthHelper(SingleSourceMovesTreeNode* source)
{
	int left, right;
	if (source == NULL)
		return 0;
	left = getTreeDepthHelper(source->next_move[LEFT]);
	right = getTreeDepthHelper(source->next_move[RIGHT]);
	return (max(left, right) + 1);
}

int getMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

bool isEmptyList(SingleSourceMovesList* lst)
{
	if (lst->head == NULL)
		return true;
	return false;
}

void insertNodeToStartOfMovesList(SingleSourceMovesList* lst, SingleSourceMovesListCell* node)
{
	node->next = lst->head;
	lst->head = node;
	if(isEmptyList(lst))
		lst->tail = node;
}

SingleSourceMovesListCell* createNewMovesListNode(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* node;
	node = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	if (node == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	node->captures = captures;
	node->position = pos;
	node->next = next;
	return node;
}

void insertDataToStartOfMovesList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures)
{
	SingleSourceMovesListCell* node;
	node = createNewMovesListNode(pos, captures, NULL);
	insertNodeToStartOfMovesList(lst, node);
}

void freeMovesList(SingleSourceMovesList* lst)
{
	SingleSourceMovesListCell* curr = lst->head, * tmp;
	while (curr != NULL)
	{
		tmp = curr->next;
		freeMovesListNode(curr);
		curr = tmp;
	}
	free(lst);
}

void freeMovesListNode(SingleSourceMovesListCell* node)
{
	freeCheckersPos(node->position);
	free(node);
}
