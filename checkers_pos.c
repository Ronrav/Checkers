#include "checkers_pos.h"

void initCheckersPos(checkersPos* p)
{
	p = (checkersPos*)malloc(sizeof(checkersPos));
	if (p == NULL)
	{
		printf("Memory allocation failed. Exiting");
		exit(1);
	}
}

bool isCheckersPosValid(int row, int col)
{
	if (row >= 0 && col >= 0)
		return true;
	return false;
}

void freeCheckersPos(checkersPos* p)
{
	free(p);
}

checkersPos* getCurrentPos(int row, int col)
{
	checkersPos* pos;
	initCheckersPos(pos);
	pos->row = row + 'A'; //set matching char row num
	pos->col = col + '0';	//set matching char col num
	return pos;
}