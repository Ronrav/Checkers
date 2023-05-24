#ifndef BOARD_H
#define BOARD_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

/*This function reviews the board after each turn, checking for winner and collecting stats*/
bool reviewBoard(Board board, Player* winner, int pieces_cnt[], int max_captures[]);

/*This function initialise a checkers board for the start of the game*/
void initBoard(Board board);

/*This function defaults all of the board values to the EMPTY const*/
void zeroBoard(Board board);

/*This function checks if Player1 has won the game according to conditions*/
bool isPlayer1Winner(Board board, int rival_pieces_num);

/*This function checks if Player2 has won the game according to conditions*/
bool isPlayer2Winner(Board board, int rival_pieces_num);

/*This function retrievs the number of each player's pieces on the board*/
void getPiecesCnt(Board board, int* p1_cnt, int* p2_cnt);

/*This function check if one of the players has won the game*/
bool checkForWinner(Board board, Player* winner, int p1_cnt, int p2_cnt);

#endif