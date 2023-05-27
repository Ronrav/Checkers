#include "board.h"

void printBoard(Board board)
{
	int i, j;
	printBoardHeader();
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("|%c|", 'A' + i);
		for (j = 0; j < BOARD_SIZE; j++)
		{
			printf("%c|", board[i][j]);
		}
		printSepLine();
	}
}

void printBoardHeader()
{
	int i;
	printSepLine();
	printf("+ |");
	for (i = 1; i <= BOARD_SIZE; i++)
	{
		printf("%d|", i);
	}
	printSepLine();
}

void printSepLine()
{
	int i;
	printf("\n");
	for (i = 0; i <= BOARD_SIZE; i++)
		printf("+-");
	printf("+\n");
}

void initBoard(Board board)
{
	zeroBoard(board);
	int i, j;
	for (i = 0; i < STARTING_LINES; i++)
	{
		for (j = (1 + i) % 2; j < BOARD_SIZE; j = j + 2)
		{
			board[i][j] = PLAYER1;
		}
	}
	for (i = BOARD_SIZE - STARTING_LINES; i < BOARD_SIZE; i++)
	{
		for (j = (1 + i) % 2; j < BOARD_SIZE; j = j + 2)
		{
			board[i][j] = PLAYER2;
		}
	}
}

void zeroBoard(Board board)
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = EMPTY;
}

bool isPlayer1Winner(Board board, int rival_pieces_num)
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (board[BOARD_SIZE - 1][i] == PLAYER1)
			return true;
	}
	if (rival_pieces_num == 0)
		return true;
	return false;
}

bool isPlayer2Winner(Board board, int rival_pieces_num)
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (board[0][i] == PLAYER2)
			return true;
	}
	if (rival_pieces_num == 0)
		return true;
	return false;
}

bool reviewBoard(Board board, Player* winner, int pieces_cnt[], int max_captures[])
{
	int p1_cnt, p2_cnt, captures1, captures2;
	getPiecesCnt(board, &p1_cnt, &p2_cnt);
	bool has_won = checkForWinner(board, winner, p1_cnt, p2_cnt);	//check if game has ended according to rules
	captures1 = pieces_cnt[0] - p1_cnt;	//calculate eaten pieces per turn
	captures2 = pieces_cnt[1] - p2_cnt;
	pieces_cnt[0] = p1_cnt;		//update num of pieces on board
	pieces_cnt[1] = p2_cnt;
	if (captures1 > max_captures[0])	//set max captures
		max_captures[0] = captures1;
	if (captures2 > max_captures[1])
		max_captures[0] = captures2;
	return has_won;
}

void getPiecesCnt(Board board, int* p1_cnt, int* p2_cnt)
{
	int i, j, cnt1 = 0, cnt2 = 0;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == PLAYER1)
				cnt1++;
			else if (board[i][j] == PLAYER2)
				cnt2++;
		}
	}
	*p1_cnt = cnt1;
	*p2_cnt = cnt2;
}

bool checkForWinner(Board board, Player* winner, int p1_cnt, int p2_cnt)
{
	bool has_won = false;
	if (isPlayer1Winner(board, p2_cnt))
	{
		*winner = PLAYER1;
		has_won = true;
	}
	else if (isPlayer2Winner(board, p1_cnt))
	{
		*winner = PLAYER2;
		has_won = true;
	}
	return has_won;
}

