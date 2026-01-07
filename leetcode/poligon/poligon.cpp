#include <vector>
#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>

// use c++11

typedef std::pair< int, int > point;
typedef std::pair< point, point > line;

void change_direction( line& value ) {
	std::swap( value.first, value.second );
}

enum status { no, direct, next };

status check_next(const line& lv, const line& rv) {
	return lv.second == rv.first ? next :
		lv.second == rv.second ? direct : no;
}

void resolve( std::vector<line>& value ) {
	for (std::vector<line>::iterator lit = value.begin(); lit != value.end() - 1; ++lit) {
		for (std::vector<line>::iterator rit = lit + 1; rit != value.end(); ++rit) {
			const status s = check_next(*lit, *rit);
			if (s != no) {
				if (s == direct)
					change_direction(*rit);
				std::iter_swap((lit + 1), rit);
				break;
			}
		}
	}
}

void print(const std::vector<line>& value) {
	std::for_each( value.begin(), value.end(), [](const line& value) {
		std::cout << "line ( x: " << value.first.first << ", y: " << value.first.second <<
			" ) ( x: " << value.second.first << ", y: " << value.second.second << " )" << std::endl;
	});
}

int main() {

	std::vector<line> poligon = { 
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

