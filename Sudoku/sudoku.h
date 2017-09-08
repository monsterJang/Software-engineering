#pragma once
class Sudoku
{
public:
	Sudoku();
	~Sudoku();
	void SudokuGenerate();
	void SudokuPrint();
private:
	int sudoku[9][9];
	int trynum[9];
	void getNext(int &i, int &j);
	bool judge(int row, int col, int curnum);
	bool dfs(int i, int j);
	void Generate();
	void print();
};
