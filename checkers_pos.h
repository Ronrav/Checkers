#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct _checkersPos {
	char row, col;
}checkersPos;

//allocate and verify memory for checkersPos
void initCheckersPos(checkersPos* p);

//verify a checkersPos is within the board borders
bool isCheckersPosValid(int row, int col);

void freeCheckersPos(checkersPos* p);
