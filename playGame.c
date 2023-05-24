#include "playGame.h"

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
