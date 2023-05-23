#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "checkers_pos.h"
#include "multipleSourceMovesList.h"
#include "singleSourceList.h"
#include "singleSourceMovesTree.h"
#include "board.h"	

/*This function operates a player's single turn*/
void Turn(Board board, Player player);

/*This function compares two potential moves and returns an SingleSourceMovesList object that holds the better move*/
SingleSourceMovesList* getBetterMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2, Player player);

/*This function receives the board and a performed move, and updates the board accordingly*/
void updateBoard(Board board, SingleSourceMovesList* moves_list, Player player);