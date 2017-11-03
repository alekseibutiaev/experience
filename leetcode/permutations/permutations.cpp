#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

class Solution {
public:
	std::vector<std::vector<int>> permute(std::vector<int>& nums) {
		std::vector<std::vector<int>> result;
		std::vector<int> indexes( nums.size() );
		std::vector<int> ind( nums.size() );
		for (std::size_t index = 0; index < nums.size(); ++index)
			ind[index] = static_cast<int>(index);
		do {
			if (checkup_indexes(indexes, ind)) {
				std::vector<int> tmp(nums.size());
				for (std::size_t i = 0; i < nums.size(); ++i)
					tmp[i] = nums[indexes[i]];
				result.push_back(tmp);
			}
		} while (!incriment(indexes));
		return result;
	}
private:
	bool checkup_indexes(std::vector<int> value, const std::vector<int>& indexes) {
		std::sort( value.begin(), value.end() );
		return std::equal(value.begin(), value.end(), indexes.begin());
	}
	bool incriment( std::vector<int>& value ) {
		const std::size_t max = value.size();
		for (std::size_t index = 0; index < max; ++index)
			if (++value[index] >= static_cast<int>(max))
				value[index] = 0;
			else
				return false;
		return true;
	}
};

int main() {
	int a[] = { 1, 2, 3 };
	std::next_permutation( &a[0], &a[2] );
	Solution s;
	std::vector<int> input = { 1,2,3,5 };
	std::vector<std::vector<int>> r = s.permute(input);
	std::for_each(r.begin(), r.end(), [](const std::vector<int>& value) {
		std::copy(value.begin(), value.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	});

	return 0;
}

