#include <stdio.h>
#include <stdbool.h>

typedef struct _checkersPos {
	char row, col;
}checkersPos;

//allocate and verify memory for checkersPos
void initCheckersPos(checkersPos* p);

bool isCheckersPosValid(int row, int col);
