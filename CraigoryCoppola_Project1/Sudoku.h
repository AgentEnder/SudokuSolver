#pragma once

struct SudokuPuzzle {
	short data[81];
};

class Sudoku
{
private:
	SudokuPuzzle puzzle;
public:
	Sudoku();
	~Sudoku();

	Sudoku(int ** puzzle_mtx); //Constructor given a 2*2 matrix
	Sudoku(int * puzzle_arr); //Constructor given a 1*81 matrix

	void Display();

	bool operator=(Sudoku other);
};

