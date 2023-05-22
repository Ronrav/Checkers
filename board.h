#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "checkers_pos.h"
#include "multipleSourceMovesList.h"
#include "singleSourceList.h"
#include "singleSourceMovesTree.h"
#include "turn.h"	
#define BOARD_SIZE 8
#define EMPTY ' '
#define STARTING_LINES 3
#define PLAYER1 'T'
#define PLAYER2 'B'
#define NUM_OF_PLAYERS 2
#define DEFAULT_NUM_OF_PIECES 12
typedef unsigned char Player;
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

void printBoard(Board board);

void printBoardHeader();

void printSepLine();

void reviewBoard(Player player1, Player player2, Player* winner);

void initBoard(Board board);

bool isPlayer1Winner(Board board);

bool isPlayer2Winner(Board board);

void PlayGame(Board board, Player starting_player);