#pragma once

struct SudokuPuzzle {
	short data[81];
};

struct StateList {
	SudokuPuzzle state;
	StateList * next = nullptr;
};

class Sudoku
{
private:
	SudokuPuzzle puzzle;
	StateList * solutions;
	int slnCount = 0;
	bool RecursiveSolver(int curr, SudokuPuzzle state);
public:
	Sudoku();
	~Sudoku();

	Sudoku(int ** puzzle_mtx); //Constructor given a 2*2 matrix
	Sudoku(int * puzzle_arr); //Constructor given a 1*81 matrix

	void Display(SudokuPuzzle state);

	StateList  * getSolutions();
	int getSlnCount();
	void Display();
	void SetBlocks();
	void HighlightImportant(int x, int y);
	bool SetCell(int value, int x, int y);
	bool CheckValid(); //Validate each row, column, and block
	bool CheckValid(int x, int y); //Check if a specific cell is valid in the current 
	bool Solve();
	bool LoadData(int * puzzle_arr); //Similar to constructor
	bool LoadData(int ** puzzle_mtx); //Similar to constructor
	bool LoadFromFile(std::string fpath);
	bool operator=(Sudoku other);

	bool CheckValid(SudokuPuzzle state);
	static bool CheckValid(int x, int y, SudokuPuzzle state);
};

