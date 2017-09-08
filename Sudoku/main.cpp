#include "sudoku.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#pragma warning(disable : 4996)

bool digitCheck(char *s)
{
	int len = strlen(s);
	rep(i, 0, len)
		if (s[i] < '0' || s[i] > '9')  return false;
	return true;
}

int main(int argc, char *argv[])
{
	freopen("sudoku.txt", "w", stdout);
	srand((unsigned int)time(NULL));
	char num[10005];
	sscanf_s(argv[2], "%s", num, 10005);
	if (!digitCheck(num))
	{
		printf("input error\n\n");
	}
	else
	{
		int n = atoi(num);
		Sudoku *sdk = new Sudoku;
		rep(i, 1, n + 1)
		{
			sdk->SudokuGenerate();
			sdk->SudokuPrint();
			putchar('\n');
		}
		delete sdk;
	}

	return 0;
}