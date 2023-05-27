#include "playGame.h"

void main()
{
	Board board;
	printf("START OF THE GAME:\n");
	initBoard(board);
	printBoard(board);
	PlayGame(board, PLAYER1);
}