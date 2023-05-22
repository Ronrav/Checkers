#include "multipleSourceMovesList.h"

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	MultipleSourceMovesList* mul_moves_lst = initDynamicMemMultipleMovesList();

	int i, j;
	SingleSourceMovesTree* moves_tree;
	SingleSourceMovesList* single_moves_lst;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				checkersPos* pos = getCurrentPos(i, j);
				//moves_tree = findSingleSourceMoves(board, pos)
				single_moves_lst = FindSingleSourceOptimalMove(moves_tree);
				insertDataToStartOfMultipleMovesList(mul_moves_lst, single_moves_lst);
			}
		}
	}
	return mul_moves_lst;
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