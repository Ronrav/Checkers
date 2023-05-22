#include "multipleSourceMovesList.h"

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{

}

void insertNodeToStartOfMultipleMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node)
{
	node->next = lst->head;
	lst->head = node;
	if (isMultipleMovesEmptyList(lst))
		lst->tail = node;
}

MultipleSourceMovesListCell* createNewMovesListNode(SingleSourceMovesList* single_moves_list, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* node = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	if (node == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	node->next = next;
	node->single_source_moves_list = single_moves_list;

}

void insertDataToStartOfMultipleMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_list)
{
	MultipleSourceMovesListCell* node = createNewMovesListNode(single_moves_list, NULL);
	lst->head = node;
	insertNodeToStartOfMultipleMovesList(lst, node);


}

bool isMultipleMovesEmptyList(MultipleSourceMovesList* lst)
{
	if (lst->head == NULL)
		return true;
	return false;
}

void freeMultipleMovesList(MultipleSourceMovesList* lst)
{
	MultipleSourceMovesListCell* curr = lst->head;
	while (curr != NULL)
	{
		freeMovesList(curr->single_source_moves_list);
		free(curr);
	}
	free(lst);
}

MultipleSourceMovesList* initDynamicMemMultipleMovesList()
{
	MultipleSourceMovesList* lst;
	lst = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	if (lst == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	makeMultipleMovesEmptyList(lst);
	return lst;
}

void makeMultipleMovesEmptyList(MultipleSourceMovesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}