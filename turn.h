#ifndef TURN_H
#define TURN_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "checkersPos.h"
#include "multipleSourceMovesList.h"
#include "singleSourceList.h"
#include "singleSourceMovesTree.h"
#include "board.h"	

/*This function operates a player's single turn*/
void Turn(Board board, Player player);

/*This function compares two potential moves and returns an SingleSourceMovesList object that holds the better move*/
SingleSourceMovesList* getBetterMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2, Player player);

/*This function compares two potential moves of Player1 and returns the better move*/
SingleSourceMovesList* getBetterBMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2);

/*This function compares two potential moves of Player2 and returns the better move*/
SingleSourceMovesList* getBetterTMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2);

/*This function receives the board and a performed move, and updates the board accordingly*/
void updateBoard(Board board, SingleSourceMovesList* moves_list, Player player);

//this function prints the player's details before his turn
void printTurnDetails(Player player, SingleSourceMovesList* lst);

#endif