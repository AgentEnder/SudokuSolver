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
	std::cout << "To load a puzzle from a file, run this executable with the filepath as a command argument" << std::endl << std::endl;
	Sudoku s;
	if (argc == 2)
	{
		std::string fpath = argv[1];
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
				std::cout << "Sudoku problem in file " + fpath + " is  incomplete!" << std::endl;
				std::cout << curr << " values found, please input a complete file." << std::endl;
				std::getchar();
				return -1;
			}
			s.LoadData(d);
		}
		istream.close();
	}
	else {
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
				while (s.CheckValid() == false || valid == false) {
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
	if (s.Solve() == true)
		s.Display();
	else
		std::cout << "This puzzle cannot be solved!" << std::endl;
	std::cout << "Press any key to continue!" << std::endl;
	std::getchar();
	std::getchar();
	std::getchar();
	return 1;
}