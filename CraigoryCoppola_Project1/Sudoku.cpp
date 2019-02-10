#include<iostream>
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
			puzzle.data[i * 9 + j] = puzzle_mtx[i][j];
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

void Sudoku::Display()
{
	for (int y = 0; y < 9; y++)
	{
		std::cout << "\t";
		if (y!= 0 && y % 3 == 0)
		{
			std::cout << "---------------------" << std::endl << "\t";
		}
		for (int x = 0; x < 9; x++)
		{
			if (x!= 0 && x%3 == 0)
			{
				std::cout << "| ";
			}
			std::cout << puzzle.data[y * 9 + x] << " ";
		}
		std::cout << std::endl;
	}
}

bool Sudoku::operator=(Sudoku other)
{
	for (int i = 0; i < 81; i++)
	{
		if (puzzle.data[i]!=other.puzzle.data[i])
		{
			return false;
		}
	}
	return true;
}
