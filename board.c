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
		for (j = 1 - i % 2; j = j + 2; j < BOARD_SIZE)
		{
			board[i][j] = PLAYER1;
		}
	}
	for (i = BOARD_SIZE - STARTING_LINES; i < BOARD_SIZE; i++)
	{
		for (j = 1 - i % 2; j = j + 2; j < BOARD_SIZE)
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

bool isPlayer1Winner(Board board)
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (board[BOARD_SIZE - 1][i] == PLAYER1)
			return true;
	}
	return false;
}

bool isPlayer2Winner(Board board)
{
	int i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		if (board[0][i] == PLAYER2)
			return true;
	}
	return false;
}

void PlayGame(Board board, Player starting_player)
{
	if (starting_player != PLAYER1 && starting_player != PLAYER2)
	{
		printf("Error: Wrong player selection");
		exit(1);
	}
	int start, i;
	if (starting_player == PLAYER1)
		start = 0;
	else
		start = 1;

	int pieces_cnt[NUM_OF_PLAYERS] = { DEFAULT_NUM_OF_PIECES };
	int max_captures[NUM_OF_PLAYERS] = { 0 };
	int total_captures[NUM_OF_PLAYERS] = { 0 };
	char players[NUM_OF_PLAYERS];
	players[0] = PLAYER1;
	players[1] = PLAYER2;
	bool flag = false;
	while (!flag)
	{
		for (i = start; i < NUM_OF_PLAYERS; i++)
		{
			Turn(board, players[i]);
			//review board and check for winners
		}
	}

}

bool reviewBoard(Board board, Player* winner)
{
	if(isPlayer1Winner(board));
	{
		*winner = PLAYER1;
		return true;
	}
	isPlayer2Winner(board);
	{
		*winner = PLAYER2;
		return true;
	}
}
