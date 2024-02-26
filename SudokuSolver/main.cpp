#include "./src/sudoku.h"

/*
Input:
4
1 4 3 2
0 0 1 4
4 1 2 3
2 3 0 0

6
1 0 3 2 0 0
0 0 5 4 0 3
4 0 2 0 0 5
2 3 0 0 0 1
0 0 0 0 0 4
0 0 0 5 0 0

9
0 0 3 0 9 2 0 0 0
4 0 0 0 3 0 0 1 0
2 7 0 0 0 0 0 0 0
0 1 0 3 0 0 0 0 8
0 5 0 1 6 7 0 3 0
3 0 0 0 0 8 0 6 0
0 0 0 0 0 0 0 5 3
0 3 0 0 8 0 0 0 9
0 0 0 6 2 0 1 0 0
*/

int main(int argc, char** argv) {
	size_t size = 0;
	std::cin >> size;
	if (size <= 0) {
		std::cerr << "Invalid field";
		return -1;
	}
	
    sudoku::Board board(size);
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			std::cin >> board(i, j);
		}
	}
	sudoku::Solver solver(board);
	sudoku::Board res = solver.solve();
	sudoku::print(res);
	return 0;
}