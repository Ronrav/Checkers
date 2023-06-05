#include "multipleSourceMovesList.h"

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	MultipleSourceMovesList* mul_moves_lst = initDynamicMemMultipleMovesList();

	int i, j;
	SingleSourceMovesTree* moves_tree;
	SingleSourceMovesList* single_moves_lst;
	checkersPos* pos;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				pos = getCurrentPos(i, j);
				moves_tree = FindSingleSourceMoves(board, pos);
				single_moves_lst = FindSingleSourceOptimalMove(moves_tree);
				if (isPossibleMove(*single_moves_lst))
					insertDataToPlayersPlaceInList(mul_moves_lst, single_moves_lst, player);
			}
		}
	}
	return mul_moves_lst;
}

void insertDataToPlayersPlaceInList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_lst, Player player)
{
	if (player == PLAYER1)
		insertDataToStartOfMultipleMovesList(lst, single_moves_lst);
	if (player == PLAYER2)
		insertDataToEndOfMultipleMovesList(lst, single_moves_lst);
}

bool isPossibleMove(SingleSourceMovesList lst)
{
	if (lst.head == lst.tail)
		return false;
	return true;
}

void insertNodeToStartOfMultipleMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node)
{
	if (isMultipleMovesEmptyList(lst))
		lst->tail = node;
	else
		node->next = lst->head;
	lst->head = node;
	
}

void insertNodeToEndOfMultipleMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* node)
{
	if (isMultipleMovesEmptyList(lst))
		lst->head = node;
	else
		lst->tail->next = node;
	lst->tail = node;

}

MultipleSourceMovesListCell* createNewMultipleMovesListNode(SingleSourceMovesList* single_moves_list, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* node = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	if (node == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	node->next = next;
	node->single_source_moves_list = single_moves_list;
	return node;
}

void insertDataToStartOfMultipleMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_list)
{
	MultipleSourceMovesListCell* node = createNewMultipleMovesListNode(single_moves_list, NULL);
	if (node == NULL)
		exit(1);
	insertNodeToStartOfMultipleMovesList(lst, node);
}

void insertDataToEndOfMultipleMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_moves_list)
{
	MultipleSourceMovesListCell* node = createNewMultipleMovesListNode(single_moves_list, NULL);
	if (node == NULL)
		exit(1);
	insertNodeToEndOfMultipleMovesList(lst, node);
}

bool isMultipleMovesEmptyList(MultipleSourceMovesList* lst)
{
	if (lst->head == NULL)
		return true;
	return false;
}

void freeMultipleMovesList(MultipleSourceMovesList* lst)
{
	MultipleSourceMovesListCell* curr = lst->head, * tmp;
	while (curr != NULL)
	{
		tmp = curr->next;
		freeMovesList(curr->single_source_moves_list);
		free(curr);
		curr = tmp;
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