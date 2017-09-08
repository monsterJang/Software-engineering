#include "Sudoku.h"
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)


Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}

void Sudoku::SudokuGenerate()
{
	Generate();
}

void Sudoku::SudokuPrint()
{
	print();
}

void Sudoku::getNext(int &i, int &j)
{
	j++;
	if (j == 9)  i++, j = 0;
}

bool Sudoku::judge(int row, int col, int curnum)
{
	// check the col
	rep(i, 0, row)
		if (sudoku[i][col] == curnum)  return false;
	// check the row
	rep(j, 0, col)
		if (sudoku[row][j] == curnum)  return false;
	// check the area
	int belongRow = row / 3 * 3;
	int belongCol = col / 3 * 3;   // get the upleft of the area
	int index = (row % 3) * 3 + (col % 3);
	while (--index >= 0)
	{
		if (sudoku[belongRow + index / 3][belongCol + index % 3] == curnum)  return false;
	}
	return true;
}

bool Sudoku::dfs(int i, int j)
{
	if (i == 9)  return true;
	for (auto &curnum : trynum)
	{
		if (judge(i, j, curnum))
		{
			sudoku[i][j] = curnum;
			int _i = i;
			int _j = j;
			getNext(_i, _j);
			if (dfs(_i, _j))  return true;
			sudoku[i][j] = 0;
		}
	}
	return false;
}

void Sudoku::Generate()
{
	rep(i, 0, 9)  sudoku[0][i] = trynum[i] = i + 1;
	swap(sudoku[0][0], sudoku[0][6]);   // required
	random_shuffle(trynum, trynum + 9);
	random_shuffle(sudoku[0] + 1, sudoku[0] + 9);
	dfs(1, 0);
}

void Sudoku::print()
{
	rep(i, 0, 9)  rep(j, 0, 9)  printf("%d%c", sudoku[i][j], " \n"[j == 8]);
}
