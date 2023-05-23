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
	int total_moves[NUM_OF_PLAYERS] = { 0 };
	char players[NUM_OF_PLAYERS];
	Player winner, most_captures_pl;
	players[0] = PLAYER1;
	players[1] = PLAYER2;
	bool has_won = false;
	while (!has_won)
	{
		for (i = start; i < NUM_OF_PLAYERS; i++)
		{
			Turn(board, players[i]);
			total_moves[i]++;
			if (reviewBoard(board, &winner, pieces_cnt, max_captures))	//returns true if a player has won the game
			{
				has_won = true;
				break;
			}
				
		}
	}
	most_captures_pl = getPlayerWithBestCaptureMove(max_captures[0], max_captures[1]);
	printWinner(winner, total_moves[i], most_captures_pl, get_max(max_captures[0], max_captures[1]));
}

bool reviewBoard(Board board, Player* winner, int pieces_cnt[], int max_captures[])
{
	int p1_cnt, p2_cnt, i, j, captures1, captures2;
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

void printWinner(Player winner, int total_moves, Player max_captures_player, int max_captures)
{
	printf(".\n.\n.\n.\n");
	printf("%c wins!\n", winner);
	printf("%c performed %d moves.\n", winner, total_moves);
	printf("%c performed the highest number of captures in a single move - %d", max_captures_player, max_captures);
}

int get_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

Player getPlayerWithBestCaptureMove(int captures1, int captures2)
{
	if (captures1 >= captures2)
		return PLAYER1;
	return PLAYER2;
}
