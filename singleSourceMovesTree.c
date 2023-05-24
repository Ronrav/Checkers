#define _CRT_SECURE_NO_WARNINGS
#include "singleSourceMovesTree.h"

//this function gets a board and chekers pos pointer.
// it returns a Single Source Moves Tree with all the possiblle moves
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src)
{
	SingleSourceMovesTree* new;
	new = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	if (new == NULL)
		exit(1);
	bool IsFirstStep = true;
	int captures_counter = 0;

	if (board[src->row - 'A'][src->col - '0' - 1] == EMPTY)
		return NULL;

	new->source = FindSingleSourcesMovesHelper(board, *src, &IsFirstStep, &captures_counter);
	return new;

}

SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos pos, bool* IsFirstStep, int* captures_counter)
{
	int right_capture_counter, left_capture_counter;
	Player player = board[pos.row - 'A'][pos.col - '0' - 1];
	checkersPos right_move_pos, left_move_pos;
	bool is_right_move_possible, is_left_move_possible;
	Board left_board, right_board;
	right_capture_counter = left_capture_counter = *captures_counter;

	SingleSourceMovesTreeNode* new = createNewTNODE(board, pos, NULL, NULL);
	if (new == NULL)
		exit(1);

	is_right_move_possible = findRightMove(board, pos, &right_move_pos, *IsFirstStep);
	is_left_move_possible = findLeftMove(board, pos, &left_move_pos, *IsFirstStep);

	if (*IsFirstStep)
		*IsFirstStep = false;

	if (!is_right_move_possible && !is_left_move_possible)
		return new;

	if (is_left_move_possible)
	{
		if (hasCaptured(pos, left_move_pos))//לעשות פונקציה
			left_capture_counter++;//למחוק גם את האכול
		fillNewBoard(board, pos, left_board, left_move_pos);
		(new->next_move)[LEFT] = FindSingleSourcesMovesHelper(left_board, left_move_pos, IsFirstStep, &left_capture_counter);
	}
	if (is_right_move_possible)
	{
		if (hasCaptured(pos, right_move_pos))//לעשות פונקציה
			right_capture_counter++;
		fillNewBoard(board, pos, right_board, right_move_pos);
		new->next_move[RIGHT] = FindSingleSourcesMovesHelper(right_board, right_move_pos, IsFirstStep, &right_capture_counter);
	}
	return new;

}
bool hasCaptured(checkersPos curr, checkersPos new)
{
	if (curr.col - new.col == 2 || curr.col - new.col == (-2))
		return true;
	return false;
}
void copyBoard(Board src, Board dest)
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
			dest[i][j] = src[i][j];
	}
}
void fillNewBoard(Board src, checkersPos curr_pos, Board dest, checkersPos new_pos)
{
	int delete_in_row, delete_in_col;
	char p = src[curr_pos.row - 'A'][curr_pos.col - '0' - 1];
	copyBoard(src, dest);
	dest[curr_pos.row - 'A'][curr_pos.col - '0' - 1] = EMPTY;
	dest[new_pos.row - 'A'][new_pos.col - '0' - 1] = p;
	if (hasCaptured(curr_pos, new_pos))
	{
		delete_in_row = (curr_pos.row - 'A' + new_pos.row - 'A') / 2;

		delete_in_col = (curr_pos.col - '0' - 1 + new_pos.col - '0' - 1) / 2;

		dest[delete_in_row][delete_in_col] = ' ';

	}
}

bool findRightMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step)
{
	bool flag;
	Player p = board[pos.row - 'A'][pos.col - '0' - 1];
	if (p == 'B')
		flag = findRightMoveForBPlayer(board, pos, new_pos, is_first_step);
	else
		flag = findRightMoveForTPlayer(board, pos, new_pos, is_first_step);

	return flag;
}

bool findLeftMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step)
{
	bool flag;
	Player p = board[pos.row - 'A'][pos.col - '0' - 1];
	if (p == 'B')
		flag = findLeftMoveForBPlayer(board, pos, new_pos, is_first_step);
	else
		flag = findLeftMoveForTPlayer(board, pos, new_pos, is_first_step);

	return flag;
}


bool findRightMoveForTPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step)
{
	new_pos->row = new_pos->col = NOT_FOUND;
	if (pos.col == T_LAST_IN_ROW)
		return false;

	if (pos.col == T_LAST_IN_ROW + 1 && board[pos.row - 'A' + 1][T_LAST_IN_ROW - 1 - '0'] != EMPTY)
		return false;

	if (is_first_step)
	{
		if (board[pos.row - 'A' + 1][pos.col - '0' - 2] == EMPTY)
		{
			new_pos->row = pos.row + 1;
			new_pos->col = pos.col - 1;
			return true;
		}
	}


	if (pos.col > T_LAST_IN_ROW + 1 && board[pos.row - 'A' + 1][pos.col - '0' - 2] == 'B' && board[pos.row - 'A' + 2][pos.col - '0' - 3] == EMPTY)
	{
		//
		new_pos->row = pos.row + 2;
		new_pos->col = pos.col - 2;
		return true;
	}


	return false;

}
bool findLeftMoveForTPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step)
{
	new_pos->row = new_pos->col = NOT_FOUND;
	if (pos.col == T_FIRST_IN_ROW)
		return false;

	if (pos.col == T_FIRST_IN_ROW - 1 && board[pos.row - 'A' + 1][T_FIRST_IN_ROW - '0'] != EMPTY)
		return false;

	if (is_first_step)
	{
		if (board[pos.row - 'A' + 1][pos.col - '0'] == EMPTY)
		{
			new_pos->row = pos.row + 1;
			new_pos->col = pos.col + 1;
			return true;
		}
	}

	if (pos.col < T_FIRST_IN_ROW - 1 && board[pos.row - 'A' + 1][pos.col - '0'] == 'B' && board[pos.row - 'A' + 2][pos.col - '0' + 1] == EMPTY)
	{
		new_pos->row = pos.row + 2;
		new_pos->col = pos.col + 2;
		return true;
	}

	return false;

}
bool findRightMoveForBPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step)
{
	new_pos->row = new_pos->col = NOT_FOUND;
	if (pos.col == B_LAST_IN_ROW)
		return false;

	if (pos.col == B_LAST_IN_ROW - 1 && board[pos.row - 'A' - 1][B_LAST_IN_ROW - '0' - 2] != EMPTY)
		return false;

	if (is_first_step)
	{
		if (board[pos.row - 'A' - 1][pos.col - '0'] == EMPTY)
		{
			new_pos->row = pos.row - 1;
			new_pos->col = pos.col + 1;
			return true;
		}
	}

	if (pos.col > B_FIRST_IN_ROW - 1 && board[pos.row - 'A' - 1][pos.col - '0'] == 'T' && board[pos.row - 'A' - 2][pos.col - '0' + 1] == EMPTY)
	{
		new_pos->row = pos.row - 2;
		new_pos->col = pos.col + 2;
		return true;
	}

	return false;

}
bool findLeftMoveForBPlayer(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step)
{
	new_pos->row = new_pos->col = NOT_FOUND;
	if (pos.col == B_FIRST_IN_ROW)
		return false;

	if (pos.col == B_FIRST_IN_ROW + 1 && board[pos.row - 'A' - 1][B_FIRST_IN_ROW - 1 - '0'] != EMPTY)
		return false;

	if (is_first_step)
	{
		if (board[pos.row - 'A' - 1][pos.col - '0' - 2] == EMPTY)
		{
			new_pos->row = pos.row - 1;
			new_pos->col = pos.col - 1;
			return true;
		}
	}

	if (pos.col > B_FIRST_IN_ROW + 1 && board[pos.row - 'A' - 1][pos.col - '0' - 2] == 'T' && board[pos.row - 'A' - 2][pos.col - '0' - 3] == EMPTY)
	{
		new_pos->row = pos.row - 2;
		new_pos->col = pos.col - 2;
		return true;
	}

	return false;

}

SingleSourceMovesTreeNode* createNewTNODE(Board pboard, checkersPos pos, SingleSourceMovesTreeNode* leftp, SingleSourceMovesTreeNode* rightp)
{
	SingleSourceMovesTreeNode* res;
	res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (res == NULL)
		exit(1);
	res->next_move[LEFT] = leftp;
	res->next_move[RIGHT] = rightp;
	copyBoard(pboard, res->board);
	return res;

}
void printTree(SingleSourceMovesTree t)
{
	helper(t.source);
}
void helper(SingleSourceMovesTreeNode* r)
{
	if (r == NULL)
		return;


	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("%c ", r->board[i][j]);
		printf("\n");
	}
	if ((r->next_move)[LEFT] != NULL)
		helper(r->next_move[LEFT]);
	if (r->next_move[RIGHT] != NULL)
		helper(r->next_move[RIGHT]);
}

