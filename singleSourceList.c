#include "singleSourceList.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	int max_captures = getMaxCaptures(moves_tree);
	SingleSourceMovesList* lst = initDynamicMemList();
	bool found = false;
	if (max_captures == 0)
	{
		if(moves_tree->source->next_move[LEFT] != NULL)// && moves_tree->source->pos->col != NOT_FOUND)
			insertDataToStartOfMovesList(lst, moves_tree->source->next_move[LEFT]->pos, 0);
		else if (moves_tree->source->next_move[RIGHT] != NULL)// && moves_tree->source->pos->col != NOT_FOUND)
			insertDataToStartOfMovesList(lst, moves_tree->source->next_move[RIGHT]->pos, 0);
		insertDataToStartOfMovesList(lst, moves_tree->source->pos, 0);
	}
	else
		FindSingleSourceOptimalMoveHelper(moves_tree->source, lst, max_captures, &found);
	freeTree(moves_tree);
	return lst;
}

void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, SingleSourceMovesList* lst, int max_captures, bool* flag)
{
	bool left_flag = false, right_flag = false;
	checkersPos new_pos;
	if (source == NULL || source->pos->col == NOT_FOUND || source->pos->row == NOT_FOUND)
		return;
	if (source->total_capture_so_far == max_captures)// && (source->next_move[LEFT] == NULL && source->next_move[RIGHT] == NULL))
	{
		//copy pos
		insertDataToStartOfMovesList(lst, source->pos, source->total_capture_so_far);
		*flag = true;
		return;
	}
	FindSingleSourceOptimalMoveHelper(source->next_move[LEFT], lst, max_captures, &left_flag);
	if (left_flag)
	{
		insertDataToStartOfMovesList(lst, source->pos, source->total_capture_so_far);
		*flag = true;
	}
	else
	{
		FindSingleSourceOptimalMoveHelper(source->next_move[RIGHT], lst, max_captures, &right_flag);
		if (right_flag)
		{
			insertDataToStartOfMovesList(lst, source->pos, source->total_capture_so_far);
			*flag = true;
		}
	}

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
	return (getMax(left, right) + 1);
}

int getMaxCaptures(SingleSourceMovesTree* moves_tree)
{
	if (moves_tree->source == NULL)
		return NULL_TREE;
	int max = 0;
	getMaxCapturesHelper(moves_tree->source, &max);
	return max;
}

void getMaxCapturesHelper(SingleSourceMovesTreeNode* source, int* max)
{
	int left, right;
	if (source == NULL)
		return;
	if (source->next_move[LEFT] == NULL && source->next_move[RIGHT] == NULL && source->total_capture_so_far > *max)
		*max = source->total_capture_so_far;
	else
	{
		getMaxCapturesHelper(source->next_move[LEFT], max);
		getMaxCapturesHelper(source->next_move[RIGHT], max);
	}
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
	if (isEmptyList(lst))
		lst->tail = node;
	else
		node->next = lst->head;
	lst->head = node;
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
	node->position = initCheckersPos();
	node->position->row = pos->row;
	node->position->col = pos->col;
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
