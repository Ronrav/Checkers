#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include "board.h"
#include "turn.h"

/*This function starts and completes the gameplay according to instructions*/
void PlayGame(Board board, Player starting_player);

/*Print the game winner and required stats*/
void printWinner(Player winner, int total_moves, Player max_captures_player, int max_captures);

/*return the player that made the move with the highest number of captures*/
Player getPlayerWithBestCaptureMove(int captures1, int captures2);

/*return the max num between a,b*/
int get_max(int a, int b);

#endif // !PLAY_GAME_H