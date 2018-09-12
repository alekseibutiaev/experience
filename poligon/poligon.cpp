#include <vector>
#include <utility>
#include <iostream>
#include <iterator>
#include <algorithm>

// use c++11

enum status { no, revers, next };

using point_t = std::pair<int, int>;
using line_t = std::pair<point_t, point_t>;
using polygon_t = std::vector<line_t>;

void change_direction(line_t& value ) {
	std::swap(value.first, value.second);
}

status check_next(const line_t& lv, const line_t& rv) {
	return lv.second == rv.first ? next : lv.second == rv.second ? revers : no;
}

void resolve(polygon_t& value ) {
	for(polygon_t::iterator lit = value.begin(); lit != value.end() - 1; ++lit) {
		for (polygon_t::iterator rit = lit + 1; rit != value.end(); ++rit) {
			const status s = check_next(*lit, *rit);
			if (s != no) {
				if (s == revers)
					change_direction(*rit);
				std::iter_swap((lit + 1), rit);
				break;
			}
		}
	}
}

void print(const polygon_t& value) {
	std::for_each( value.begin(), value.end(), [](const line_t& value) {
		std::cout << "line ( x: " << value.first.first << ", y: " << value.first.second <<
			" ) ( x: " << value.second.first << ", y: " << value.second.second << " )" << std::endl;
	});
}

int main() {

  polygon_t poligon = {
		{ { 3, 5 }, { 5, 4 } },
		{ { 3, 1 }, { 1, 3 } },
		{ { 5, 2 }, { 5, 4 } },
		{ { 1, 3 }, { 3, 5 } },
		{ { 5, 2 }, { 3, 1 } },
	};

	print(poligon);
	std::cout << std::endl;
	resolve(poligon);
	print(poligon);


	return 0;
}
