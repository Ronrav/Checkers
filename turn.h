#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "checkers_pos.h"
#include "multipleSourceMovesList.h"
#include "singleSourceList.h"
#include "singleSourceMovesTree.h"
#include "board.h"	

void Turn(Board board, Player player);

SingleSourceMovesList* getBetterMove(SingleSourceMovesList* move1, SingleSourceMovesList* move2, Player player);

void updateBoard(Board board, SingleSourceMovesList* moves_list, Player player);