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

/*This function prints a checkers board in a proper format*/
void printBoard(Board board);

/*This function prints a checkers board header*/
void printBoardHeader();

/*side function for board printing*/
void printSepLine();

bool reviewBoard(Board board, Player* winner, int pieces_cnt[], int max_captures[]);

/*This function initialise a checkers board for the start of the game*/
void initBoard(Board board);

/*This function checks if one of Player1 pieces reached the end of the board*/
bool isPlayer1Winner(Board board, int rival_pieces_num);

/*This function checks if one of Player2 pieces reached the end of the board*/
bool isPlayer2Winner(Board board, int rival_pieces_num);

/*This function starts and completes the gameplay according to instructions*/
void PlayGame(Board board, Player starting_player);

void getPiecesCnt(Board board, int* p1_cnt, int* p2_cnt);

bool checkForWinner(Board board, Player* winner, int p1_cnt, int p2_cnt);

void printWinner(Player winner, int total_moves, Player max_captures_player, int max_captures);

Player getPlayerWithBestCaptureMove(int captures1, int captures2);

int get_max(int a, int b);