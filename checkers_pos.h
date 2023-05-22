#pragma once
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

void freeCheckersPos(checkersPos* p);

checkersPos* getCurrentPos(int row, int col);
