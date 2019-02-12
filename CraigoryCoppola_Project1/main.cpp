#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32


#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "Sudoku.h"



int main(int argc, char *argv[]) {
	Sudoku s;
	if (argc == 2)
	{
		std::string fpath = argv[1];
		s.LoadFromFile(fpath);
	}
	else {
		std::cout << "To load a puzzle from a file, run this executable with the filepath as a command argument" << std::endl << std::endl;
		s = Sudoku();
		for (int i = 0; i < 9; i++)
		{
			for (int k = 0; k < 9; k++)
			{
				std::cout << "Input cell " << i << "," << k << std::endl;
				std::cout << "Use a 0 for a blank." << std::endl;
				s.HighlightImportant(k, i);
				int in;
				std::cin >> in;
				bool valid = s.SetCell(in, k, i);
				while (s.CheckValid(k, i) == false || valid == false) {
					std::cout << "Please enter a valid number: ";
					int in;
					std::cin >> in;
					valid = s.SetCell(in, k, i);
				}
				system(CLEAR);
			}
		}
	}


	s.Display();

	if (s.CheckValid() == false)
	{
		std::cerr << "The supplied sudoku puzzle is not valid!" << std::endl;
	}

	if (s.Solve() == true) {
		int c = s.getSlnCount();
		if (c == 1)
			std::cout << "There is a unique solution!" << std::endl;
		else
			std::cout << "There are " << c << " solutions!" << std::endl;
		StateList * solutions = s.getSolutions();
		while (solutions != NULL) {
			s.Display(solutions->state);
			solutions = solutions->next;
		}
	}
	else
		std::cout << "This puzzle cannot be solved!" << std::endl;
	std::cout << "Press any key to continue!" << std::endl;
	std::getchar();
	std::getchar();
	std::getchar();
	return 1;
}