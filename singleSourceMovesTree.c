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
	int captures_counter = 0;

	if (board[src->row - 'A'][src->col - '1'] == EMPTY)
		return NULL;

	new->source = FindSingleSourcesMovesHelper(board, *src, true, &captures_counter);
	return new;

}

SingleSourceMovesTreeNode* FindSingleSourcesMovesHelper(Board board, checkersPos pos, bool IsFirstStep, int* captures_counter)
{
	bool took_first_step = false;
	int right_capture_counter, left_capture_counter;
	Player player = board[pos.row - 'A'][pos.col - '1'];
	checkersPos right_move_pos, left_move_pos;
	bool is_right_move_possible = false, is_left_move_possible = false;
	bool left_has_captured = false, right_has_captured = false;
	Board left_board, right_board;
	right_capture_counter = left_capture_counter = *captures_counter;


	SingleSourceMovesTreeNode* new = createNewTNODE(board, pos, NULL, NULL, *captures_counter);
	findPossibleMoves(board, pos, &right_move_pos, &left_move_pos, IsFirstStep, &is_right_move_possible, &is_left_move_possible);


	if (!is_right_move_possible && !is_left_move_possible)
		return new;

	left_has_captured = hasCaptured(pos, left_move_pos);
	right_has_captured = hasCaptured(pos, right_move_pos);

	if (is_left_move_possible && (left_has_captured|| IsFirstStep == true))
	{

		fillNewBoard(board, pos, left_board, left_move_pos);
		if (!left_has_captured)
			new->next_move[LEFT] = createNewTNODE(left_board, left_move_pos, NULL, NULL, *captures_counter);
		else
		{
			left_capture_counter++;
			(new->next_move)[LEFT] = FindSingleSourcesMovesHelper(left_board, left_move_pos, false, &left_capture_counter);
		}
		
	}
	if (is_right_move_possible && (right_has_captured || IsFirstStep == true))
	{
		fillNewBoard(board, pos, right_board, right_move_pos);
		if (!right_has_captured)
			new->next_move[RIGHT] = createNewTNODE(right_board, right_move_pos, NULL, NULL, *captures_counter);
		else
		{
			right_capture_counter++;
			new->next_move[RIGHT] = FindSingleSourcesMovesHelper(right_board, right_move_pos, false, &right_capture_counter);
		}
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
	char p = src[curr_pos.row - 'A'][curr_pos.col - '1'];
	copyBoard(src, dest);
	dest[curr_pos.row - 'A'][curr_pos.col - '1'] = EMPTY;
	dest[new_pos.row - 'A'][new_pos.col - '1'] = p;
	if (hasCaptured(curr_pos, new_pos))
	{
		delete_in_row = (curr_pos.row - 'A' + new_pos.row - 'A') / 2;

		delete_in_col = (curr_pos.col - '1' + new_pos.col - '1') / 2;

		dest[delete_in_row][delete_in_col] = EMPTY;

	}
}


SingleSourceMovesTreeNode* createNewTNODE(Board pboard, checkersPos pos, SingleSourceMovesTreeNode* leftp, SingleSourceMovesTreeNode* rightp, int capture_caunter)
{
	SingleSourceMovesTreeNode* res;
	res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (res == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	res->next_move[LEFT] = leftp;
	res->next_move[RIGHT] = rightp;
	res->pos = (checkersPos*)malloc(sizeof(checkersPos));
	res->total_capture_so_far = capture_caunter;
	if (res->pos == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
	res->pos->col = pos.col;
	res->pos->row = pos.row;
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

void findPossibleMoves(Board board, checkersPos pos, checkersPos* right_new_pos, checkersPos* left_new_pos, bool is_first_step, bool* is_right_possible, bool* is_left_possible)
{
	bool flag = true;
	Player p = board[pos.row - 'A'][pos.col - '1'];
	int right, left, next_row;

	initVariablesToPlayer(p, &right, &left, &next_row);

	right_new_pos->row = right_new_pos->col = left_new_pos->row = left_new_pos->col = NOT_FOUND;

	if (!pIsLeftMost(board, pos,p))
		*is_left_possible = findNextMove(board, pos, left_new_pos, is_first_step, p, left, next_row);

	if (!pIsRightMost(board, pos,p))
		*is_right_possible = findNextMove(board, pos, right_new_pos, is_first_step, p, right, next_row);


}


void initVariablesToPlayer(int p, int* right, int* left, int* next_row)
{
	if (p == 'T')
	{
		*right = T_COL_FROM_RIGHT;
		*left = T_COL_FROM_LEFT;
		*next_row = T_NEXT_ROW;
	}
	else
	{
		*right = B_COL_FROM_RIGHT;
		*left = B_COL_FROM_LEFT;
		*next_row = B_NEXT_ROW;
	}
}

bool findNextMove(Board board, checkersPos pos, checkersPos* new_pos, bool is_first_step, char p, int side, int next_row)
{
	if (is_first_step)
	{
		if (isOneStepAvailble(board, pos, side, next_row))
		{
			new_pos->row = pos.row + next_row;
			new_pos->col = pos.col + side;
			return true;;
		}
	}

	if (Is2StepsAvailable(board, pos, p, side, next_row))
	{
		new_pos->row = pos.row + 2 * next_row;;
		new_pos->col = pos.col + 2*side ;
		return true;
	}
	return false;
}

bool isOneStepAvailble (Board board, checkersPos pos, int side, int next_row)
{
	return (board[pos.row - 'A' + next_row][pos.col - '1' + side] == EMPTY);
}
bool Is2StepsAvailable(Board board, checkersPos pos,char p, int side, int next_row)
{
	char notMe;
	int newCol = pos.col - '1' + (2 * side);
	int newRow = pos.row - 'A' + (2 * next_row);

	if (p == 'B')
		notMe = 'T';
	else
		notMe = 'B';

	if (p == 'B' && pos.row == 'B')
		return false;
	if (p == 'T' && pos.row == BOARD_SIZE + 'A' - 1)
		return false;

	if (newCol >= 0 && newCol < BOARD_SIZE && newRow >= 0 && newRow < BOARD_SIZE)
	{
		if (board[newRow - next_row][newCol - side] == notMe && board[newRow][newCol] == EMPTY)
			return true;
	}
	return false;

}
bool pIsLeftMost(Board board, checkersPos pos, char player)
{
	if (player == 'B' && pos.col == B_FIRST_IN_ROW)
		return true;
	if (player == 'T' && pos.col == T_FIRST_IN_ROW)
		return true;
	return false;
}
bool pIsRightMost(Board board, checkersPos pos, char player)
{
	if (player == 'B' && pos.col == B_LAST_IN_ROW)
		return true;
	if (player == 'T' && pos.col == T_LAST_IN_ROW)
		return true;
	return false;
}

void freeTree(SingleSourceMovesTree* tree)
{
	freeTreeHelper(tree->source);
	free(tree);
}
void freeTreeHelper(SingleSourceMovesTreeNode* source)
{
	if (source == NULL)
		return;
	freeTreeHelper(source->next_move[LEFT]);
	freeTreeHelper(source->next_move[RIGHT]);
	free(source->pos);
	free(source);
}



	