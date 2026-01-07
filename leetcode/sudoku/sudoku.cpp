
#include <vector>
#include <cctype>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cctype>
#include <set>
#include <iostream>

void print(const std::vector<std::vector<char>>& board) {
	std::for_each(board.begin(), board.end(), [](const std::vector<char>& value) {
		std::copy(value.begin(), value.end(), std::ostream_iterator<char>(std::cout, " "));
		std::cout << std::endl;
	});
}

class Solution {
public:
	void solveSudoku(std::vector<std::vector<char>>& board) {
		const cell_t cell = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		const std::vector<cell_t> row( 9, cell);
		field_t field(9, row);
		if (fill_filed(board, field))
			solution(field, board);
	}
private:
	typedef std::set<int> cell_t;
	typedef std::vector<std::vector<cell_t>> field_t;
private:

	bool solution(const field_t& field, std::vector<std::vector<char>>& board ) {
		size_t y = 0;
		size_t x = 0;
		if (is_resolve(field, y, x)) {
			for (size_t y = 0; y < 9; ++y)
				for (size_t x = 0; x < 9; ++x)
					board[y][x] = static_cast<char>( *field[y][x].begin() + '0' );
			return true;
		}
		const cell_t& cell = field[y][x];
		for (cell_t::const_iterator it = cell.begin(); it != cell.end(); ++it) {
			const unsigned char v = *it;
			field_t tmp = field;
			if (set_field(y, x, *it, tmp) && solution(tmp, board))
				return true;
		}
		return false;
	}

	bool fill_filed(const std::vector<std::vector<char>>& board, field_t& field) {
		for (size_t y = 0; y < 9; ++y)
			for (size_t x = 0; x < 9; ++x) {
				if (const int value = std::isdigit(board[y][x]) ? board[y][x] - '0' : 0 ) {
					if (!set_field(y, x, value, field))
						return false;
				}
			}
		return true;
	}

	bool is_resolve(const field_t& field, size_t& _y, size_t& _x ) {
		for (size_t y = 0; y < 9; ++y) 
			for (size_t x = 0; x < 9; ++x)
				if (1 < field[y][x].size()) {
					_y = y;
					_x = x;
					return false;
				}
		return true;
	}

	bool checkup_cell(const size_t y, const size_t x, std::vector<std::vector<cell_t>>& field) {
		const int value = *field[y][x].begin();
		for (size_t i = 0; i < 9; ++i)
			if ( !test_cell( y, x, i, x, value, field ) )
				return false;
		for (size_t i = 0; i < 9; ++i)
			if ( !test_cell(y, x, y, i, value, field ) )
				return false;
		for(size_t yy = 0; yy < 3; ++yy)
			for (size_t xx = 0; xx < 3; ++xx) {
				const size_t _xx = x / 3 * 3 + xx;
				const size_t _yy = y / 3 * 3 + yy;
				if( !test_cell(y, x, _yy, _xx, value, field) )
					return false;
			}
		return true;
	}

	bool test_cell(const size_t& y, const size_t& x, const size_t& _y, const size_t& _x,
			const int& value, std::vector<std::vector<cell_t>>& field) {
		if (x == _x && y == _y)
			return true;
		cell_t& cell = field[_y][_x];
		const size_t psize = cell.size();
		cell.erase(value);
		if (psize == 2 && 1 == cell.size())
			return checkup_cell(_y, _x, field);
		return !cell.empty();
	}

	bool set_field(const size_t y, const size_t x, const int value, std::vector<std::vector<cell_t>>& field) {
		cell_t& cell = field[y][x];
		if (cell.find(value) != cell.end()) {
			cell = cell_t(&value, &value + 1);
			return checkup_cell( y, x, field );
		}
		return false;
	}
};

int main()
{
	std::vector<std::vector<char>> board = {
		{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
		{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
		{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
		{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
		{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
		{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
		{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
		{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
		{ '.', '.', '.', '.', '8', '.', '.', '7', '9' },
	};
	print(board);
	std::cout << std::endl;
	Solution s;
	s.solveSudoku(board);
	print(board);

  return 0;
}

