#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32


#include<iostream>
#include "Sudoku.h"



int main() {
	Sudoku s = Sudoku();

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
			while (s.CheckValid() == false || valid == false) {
				std::cout << "Please enter a valid number: ";
				int in;
				std::cin >> in;
				valid = s.SetCell(in, k, i);
			}
			system(CLEAR);
		}
	}

	s.Display();
	s.Solve();
	s.Display();
	std::getchar();
	std::getchar();
	std::getchar();
}