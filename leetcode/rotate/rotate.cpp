#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>

void print(const std::vector<std::vector<int>>& p) {
	std::for_each(p.begin(), p.end(), [](const std::vector<int>& value) {
		std::copy(value.begin(), value.end(), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl; });
	std::cout << "****" << std::endl;
}


class Solution {
public:
	void rotate(std::vector<std::vector<int>>& matrix) {
		try {
			const std::size_t _x = matrix.size();
			const std::size_t _y = matrix[0].size();
			std::vector<std::vector<int>> r(_y, std::vector<int>(_x, 0));
			print(r);
			for (size_t y = 0; y < _y; ++y) {
				for (size_t x = 0; x < _x; ++x)
					r.at( y ).at( _x - 1 - x ) = matrix.at(x).at(y);
			}
			matrix = r;
		}
		catch (const std::exception& /*e*/) {
		}
	}
};


int main()
{
	Solution s;
	std::vector<std::vector<int>> p = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
	print(p);
	s.rotate(p);
	print(p);

  return 0;
}

