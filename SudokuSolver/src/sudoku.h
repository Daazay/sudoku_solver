#pragma once
#include <utility>
#include <iostream>

namespace sudoku {
	class Board;
	class Solver;

	void print(Board& b);

	///////////////////////////////////////////////////////////

	class Board {
	public:
		Board(const size_t size) {
			_size = size;
			_data = new int* [_size];
			for (size_t i = 0; i < _size; ++i) {
				_data[i] = new int[_size] {0};
			}
			_sq_size = _size;
			size_t sq_size = size - 1;
			while (sq_size > 1) {
				// squares with side 3 are preferable
				if (_sq_size == 3) break;
				if (_size % sq_size == 0) {
					_sq_size = sq_size;
				}
				sq_size--;
			}
		}
		Board(const Board& other) {
			_size = other._size;
			_data = new int* [_size];
			_sq_size = other._sq_size;
			for (size_t i = 0; i < _size; ++i) {
				_data[i] = new int[_size] {0};
			}
			for (size_t i = 0; i < _size; ++i) {
				for (size_t j = 0; j < _size; ++j) {
					_data[i][j] = other._data[i][j];
				}
			}
		}
		~Board() {
			for (size_t i = 0; i < _size; ++i) {
				delete[] _data[i];
			}
			delete[] _data;
		}
	public:
		size_t sq_size() const { return _sq_size; }
		size_t size() const { return _size; }
		int& operator()(const size_t i, const size_t j) {
			return _data[i][j];
		}
		int operator()(const size_t i, const size_t j) const {
			return _data[i][j];
		}
	private:
		size_t _sq_size = 0;
		size_t _size = 0;
		int** _data = nullptr;
	};

	class Solver {
	public:
		Solver(const Board& b) : _b{ b } {}
	public:
		Board solve() {
			solve(0, 0);
			return _b;
		}

		bool solved(Board& b) const {
			for (size_t i = 0; i < _b.size(); ++i) {
				for (size_t j = 0; j < _b.size(); ++j) {
					if (_b(i, j) == 0) return false;
				}
			}
			return true;
		}

	private:
		bool contains(const size_t x, const size_t y, const int value) {
			bool vertical = false;
			bool horizontal = false;
			bool square = false;

			// vertical
			for (size_t i = 0; i < _b.size(); ++i) {
				if (_b(i, x) == value) {
					vertical = true;
				}
			}
			// horizontal
			for (size_t i = 0; i < _b.size(); ++i) {
				if (_b(y, i) == value) {
					horizontal = true;
				}
			}
			// square
			size_t sx = ((int)(x / _b.sq_size())) * _b.sq_size();
			size_t sy = ((int)(y / _b.sq_size())) * _b.sq_size();
			for (size_t dy = 0; dy < _b.sq_size(); ++dy) {
				for (size_t dx = 0; dx < _b.sq_size(); ++dx) {
					if (_b(sy + dy, sx + dx) == value) {
						square = true;
					}
				}
			}
			return !vertical && !horizontal && !square;

		}

		bool solve(const size_t x, const size_t y) {
			if (y == _b.size()) {
				return true;
			}
			if (_b(y, x) != 0) {
				auto [nextX, nextY] = next(x, y);
				return solve(nextX, nextY);
			} else {
				for (size_t i = 1; i <= _b.sq_size() * _b.sq_size(); ++i) {
					if (contains(x, y, i)) {
						_b(y, x) = i;
						auto [nextX, nextY] = next(x, y);
						if (solve(nextX, nextY)) {
							return true;
						}
						_b(y, x) = 0;
					}
				}
				return false;
			}
		}

		std::pair<size_t, size_t> next(const size_t x, const size_t y) {
			size_t nextX = (x + 1) % _b.size();
			size_t nextY = y;
			if (nextX == 0) {
				nextY = y + 1;
			}
			return { nextX, nextY };
		}
	private:
		Board _b;
	};

	void print(Board& b) {
		std::cout << std::endl;
		for (size_t i = 0; i < b.size(); ++i) {
			for (size_t j = 0; j < b.size(); ++j) {
				std::cout << b(i, j);
				if (j + 1 < b.size()) {
					std::cout << " ";
				}
			}
			std::cout << "\n";
		}
		std::cout << std::endl;
	}
}
