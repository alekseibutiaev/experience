#include <algorithm>
#include <vector>
#include <iostream>


class Solution {
public:
	double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
		if (nums1.empty() && nums2.empty())
			return 0.0;
		std::vector<int> tmp;
		std::vector<int>::const_iterator it1 = nums1.begin();
		std::vector<int>::const_iterator it2 = nums2.begin();
		for (;;) {
			if (it1 == nums1.end()) {
				tmp.insert(tmp.end(), it2, nums2.cend());
				break;
			}
			if (it2 == nums2.end()) {
				tmp.insert(tmp.end(), it1, nums1.cend());
				break;
			}
			if (*it1 <= *it2)
				tmp.push_back(*it1++);
			if (*it2 <= *it1)
				tmp.push_back(*it2++);
		}
		const unsigned int count = static_cast<unsigned int>(tmp.size());
		const unsigned int median_index[2] = { count % 2 ? count / 2 : count / 2 - 1,	count / 2 };
		return static_cast<double>(tmp[median_index[0]] + tmp[median_index[1]]) / 2;
	}

};

int main(int ac, char av[]) {

	std::vector<int> n1 = {/* 1, 6, 3, 9, 5, 6, 4, 9/**/ };
	std::vector<int> n2 = { 1/*, 2, 2, 1, 6, 8, 3, 0, 4, 9/**/ };
	std::sort(n1.begin(), n1.end());
	std::sort(n2.begin(), n2.end());
	Solution s;
	std::cout << "Result: " << s.findMedianSortedArrays(n1, n2) << std::endl;
	return 0;
}
