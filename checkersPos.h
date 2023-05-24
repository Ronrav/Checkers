#ifndef CHECKERS_POS_H
#define CHECKERS_POS_H


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _checkersPos {
	char row, col;
}checkersPos;

//allocate and verify memory for checkersPos
checkersPos* initCheckersPos();

//verify a checkersPos is within the board borders
bool isCheckersPosValid(int row, int col);

/*Free CheckersPos dynamic memroy*/
void freeCheckersPos(checkersPos* p);

/*This function receives an row and col integers between 0-7.
The function creates inits a checkersPos struct and set's it's values according to row and col*/
checkersPos* getCurrentPos(int row, int col);

#endif // CHECKERS_POS_H