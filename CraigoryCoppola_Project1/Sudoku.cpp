#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "Sudoku.h"


bool Sudoku::RecursiveSolver(int curr, SudokuPuzzle state)
{
	if (curr == 81)
	{
		if (CheckValid(state) == true) {
			StateList * temp = new StateList{ state, solutions };
			solutions = temp;
			slnCount++;
			std::cerr << "Solution found, currently at " << slnCount << " solutions" << std::endl;
			return true;
		}
		else {
			Display(state);
		}
	}
	if (state.data[curr] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			state.data[curr] = (short)i;
			if (CheckValid(curr % 9, curr / 9, state))
			{
				RecursiveSolver(curr + 1, state);
				/*if (RecursiveSolver(curr + 1, state) == true) {
					return true;
				}*/
			}
		}
	}
	else {
		if (RecursiveSolver(curr + 1, state)) {
			return true;
		}
	}
	return false;
}

Sudoku::Sudoku()
{
	puzzle = { {0} };
}

Sudoku::~Sudoku()
{
	while(solutions != nullptr){
		StateList * temp = solutions;
		solutions = temp->next;
		delete temp;
	}
}

Sudoku::Sudoku(int ** puzzle_mtx)
{
	puzzle = SudokuPuzzle();
	LoadData(puzzle_mtx);
}

Sudoku::Sudoku(int * puzzle_arr)
{
	puzzle = SudokuPuzzle();
	LoadData(puzzle_arr);
}

void Sudoku::Display(SudokuPuzzle state)
{
	std::cout << std::endl;
	int cell;
	for (int y = 0; y < 9; y++)
	{
		std::cout << "\t";
		if (y != 0 && y % 3 == 0)
		{
			std::cout << "---------------------" << std::endl << "\t";
		}
		for (int x = 0; x < 9; x++)
		{
			if (x != 0 && x % 3 == 0)
			{
				std::cout << "| ";
			}
			cell = state.data[y * 9 + x];
			if (cell > 0)
			{
				std::cout << state.data[y * 9 + x] << " ";
			}
			else if (cell == 0) {
				std::cout << "- ";
			}
			else {
				std::cout << "@ ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

StateList * Sudoku::getSolutions()
{
	return solutions;
}

int Sudoku::getSlnCount()
{
	return slnCount;
}

void Sudoku::Display()
{
	Display(puzzle);
}

bool Sudoku::Solve() {
	RecursiveSolver(0, puzzle);
	return slnCount > 0;
}

bool Sudoku::LoadData(int * puzzle_arr)
{
	for (int i = 0; i < 81; i++)
	{
		puzzle.data[i] = (short)puzzle_arr[i];
	}
	return true;
}

bool Sudoku::LoadData(int ** puzzle_mtx)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			puzzle.data[i * 9 + j] = puzzle_mtx[i][j];
		}
	}
	return true;
}

bool Sudoku::LoadFromFile(std::string fpath)
{
	std::ifstream istream(fpath);
	if (istream.is_open())
	{
		std::string line;
		int curr = 0;
		int d[81];
		while (std::getline(istream, line)) {   // get a whole line
			std::stringstream ss(line);
			while (std::getline(ss, line, ' ')) {
				d[curr] = std::stoi(line);
				curr++;
			}
		}
		if (curr < 81)
		{
			std::cerr << "Sudoku problem in file " + fpath + " is  incomplete!" << std::endl;
			std::cerr << curr << " values found, please input a complete file." << std::endl;
			std::getchar();
			return false;
		}
		LoadData(d);
	}
	istream.close();
	return true;
}


bool Sudoku::CheckValid() {
	return CheckValid(puzzle);
}

bool Sudoku::CheckValid(SudokuPuzzle state)
{
	bool bitFlags[9] = { false, false, false, false, false, false, false, false, false };
	short cell;
	for (int row = 0; row < 9; row++) // validate rows
	{
		for (int x = 0; x < 9; x++)
		{
			cell = state.data[row * 9 + x] - 1;
			if (cell == -1) continue;

			if (bitFlags[cell] == true)
			{
				return false;
			}
			else
			{
				bitFlags[cell] = true;
			}
		}
		for (int i = 0; i < 9; i++)
			bitFlags[i] = false;
	}

	for (int column = 0; column < 9; column++) // validate columns
	{
		for (int y = 0; y < 9; y++)
		{
			cell = state.data[y * 9 + column] - 1;
			if (cell == -1) continue;

			if (bitFlags[cell] == true)
			{
				return false;
			}
			else
			{
				bitFlags[cell] = true;
			}

		}
		for (int i = 0; i < 9; i++)
			bitFlags[i] = false;
	}
	for (int i = 0; i < 9; i++)
		bitFlags[i] = false;
	for (int block = 0; block < 9; block++) // validate blocks
	{
		int x_min = 3 * (block % 3); // Block X is 0,1,2, blocks are 3x3 so mult 3 gives the left most edge of the block.
		int y_min = 3 * (block / 3); //Integer divison causes 3* 7/3 to be 6, giving the top mmost y coordinate in a block from any y coordinate in the block.

		for (int y = y_min; y < y_min + 3; y++)
		{
			for (int x = x_min; x < x_min + 3; x++)
			{
				cell = state.data[y * 9 + x] - 1;
				if (cell == -1) continue;
				if (bitFlags[cell] == true)
				{
					std::cerr << "Block " << block << " already contains " << cell + 1 << "!\n" << std::endl;
					std::cerr << "Error found at " << x << "," << y << std::endl;
					return false;
				}
				else
				{
					bitFlags[cell] = true;
				}
			}
		}
		for (int i = 0; i < 9; i++)
			bitFlags[i] = false;
	}
	return true;
}

bool Sudoku::CheckValid(int x, int y)
{
	return CheckValid(x,y,puzzle);
}

bool Sudoku::CheckValid(int x, int y, SudokuPuzzle state)
{
	bool bitFlags[9] = { false, false, false, false, false, false, false, false, false };
	short cell;
	// validate row
	for (int x = 0; x < 9; x++)
	{
		cell = state.data[y * 9 + x] - 1;
		if (cell == -1) continue;

		if (bitFlags[cell] == true)
		{
			return false;
		}
		else
		{
			bitFlags[cell] = true;
		}
	}
	for (int i = 0; i < 9; i++)
		bitFlags[i] = false;

	// validate column
	for (int y = 0; y < 9; y++)
	{
		cell = state.data[y * 9 + x] - 1;
		if (cell == -1) continue;

		if (bitFlags[cell] == true)
		{
			return false;
		}
		else
		{
			bitFlags[cell] = true;
		}
	}

	for (int i = 0; i < 9; i++)
		bitFlags[i] = false;

	// validate block
	int block = 3 * (y / 3) + x / 3;
	int x_min = 3 * (block % 3); // Block X is 0,1,2, blocks are 3x3 so mult 3 gives the left most edge of the block.
	int y_min = 3 * (block / 3); //Integer divison causes 3* 7/3 to be 6, giving the top mmost y coordinate in a block from any y coordinate in the block.

	for (int y = y_min; y < y_min + 3; y++)
	{
		for (int x = x_min; x < x_min + 3; x++)
		{
			cell = state.data[y * 9 + x] - 1;
			if (cell == -1) continue;

			if (bitFlags[cell] == true)
			{
				return false;
			}
			else
			{
				bitFlags[cell] = true;
			}
		}
	}
	return true;
}


void Sudoku::SetBlocks() {
	for (int block = 0; block < 9; block++) // validate blocks
	{
		int x_min = 3 * (block % 3);
		int y_min = 3 * (block / 3);

		for (int y = y_min; y < y_min + 3; y++)
		{
			for (int x = x_min; x < x_min + 3; x++)
			{
				puzzle.data[y * 9 + x] = block;
			}
		}
	}
}

void Sudoku::HighlightImportant(int h_x, int h_y)
{
	std::cout << std::endl;
	int cell;
	for (int y = 0; y < 9; y++)
	{
		std::cout << "\t";
		if (y != 0 && y % 3 == 0)
		{
			std::cout << "---------------------" << std::endl << "\t";
		}
		for (int x = 0; x < 9; x++)
		{
			if (x != 0 && x % 3 == 0)
			{
				std::cout << "| ";
			}
			cell = puzzle.data[y * 9 + x];
			if (h_x == x && h_y == y)
			{
				std::cout << "? ";
			}else if (cell > 0)
			{
				std::cout << puzzle.data[y * 9 + x] << " ";
			}
			else if (cell == 0) {
				std::cout << "- ";
			}
			else {
				std::cout << "@ ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Sudoku::SetCell(int value, int x, int y)
{
	if (value < 0 || value > 9 || x < 0 || x > 9 || y < 0 || y > 9)
	{
		return false;
	}
	puzzle.data[y * 9 + x] = value;
	return true;
}

bool Sudoku::operator=(Sudoku other)
{
	for (int i = 0; i < 81; i++)
	{
		if (puzzle.data[i] != other.puzzle.data[i])
		{
			return false;
		}
	}
	return true;
}

