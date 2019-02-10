#include "Sudoku.h"



Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}

Sudoku::Sudoku(int ** puzzle_mtx)
{
	puzzle = SudokuPuzzle();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			puzzle.data[i*9+j] =  puzzle_mtx[i][j]
		}
	}
}

Sudoku::Sudoku(int * puzzle_arr)
{
	puzzle = SudokuPuzzle();
	for (int i = 0; i < 81; i++)
	{
		puzzle.data[i] = (short)puzzle_arr[i];
	}
}
