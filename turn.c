#include "turn.h"

void Turn(Board board, Player player)
{
	MultipleSourceMovesList* lst = FindAllPossiblePlayerMoves(board, player);
	MultipleSourceMovesListCell* node = lst->head->next;
	SingleSourceMovesList* best_move = lst->head->single_source_moves_list;
	while (node != NULL)
	{
		best_move = getBetterMove(node->single_source_moves_list, best_move, player);
		node = node->next;
	}
	printTurnDetails(player, best_move);
	updateBoard(board, best_move, player);
	freeMultipleMovesList(lst);
	
}
void printTurnDetails(Player player, SingleSourceMovesList* lst)
{
	printf("\n%c's turn:\n%c%c -> %c%c", player, lst->head->position->row, lst->head->position->col, lst->tail->position->row, lst->tail->position->col);
}

SingleSourceMovesList* getBetterMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2, Player player)
{
	if (move2->tail->captures < move1->tail->captures)
		return move1;
	else
		return move2;
}

SingleSourceMovesList* getBetterBMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2)
{
	if (move1->head->position->row < move2->head->position->row)
		return move1;
	else if (move1->head->position->row > move2->head->position->row)
		return move2;
	else if (move1->head->position->col < move2->head->position->col)	//starting row is equal
		return move1;
	return move2;
}

SingleSourceMovesList* getBetterTMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2)
{
	if (move1->head->position->row > move2->head->position->row)
		return move1;
	else if (move1->head->position->row < move2->head->position->row)
		return move2;
	else if (move1->head->position->col > move2->head->position->col)	//starting row is equal
		return move1;
	return move2;
}

void updateBoard(Board board, SingleSourceMovesList* moves_list, Player player)
{
	SingleSourceMovesListCell* node = moves_list->head;
	unsigned short captures = moves_list->tail->captures;
	int captured_col, captured_row, cur_col, cur_row, next_col, next_row;
	while (node->next != NULL)
	{
		cur_row = node->position->row - 'A';
		cur_col = node->position->col - '1';
		next_row = node->next->position->row - 'A';
		next_col = node->next->position->col - '1';
		
		board[next_row][next_col] = player;
		board[cur_row][cur_col] = EMPTY;
		if (captures > 0)
		{
			captured_row = (cur_row + next_row) / 2;
			captured_col = (cur_col + next_col) / 2;
			board[captured_row][captured_col] = EMPTY;
			captures--;
		}
		node = node->next;
	}
}