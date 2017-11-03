// zero-indexed.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <numeric>
#include <iostream>

int solution(std::vector<int> &A) {
	// write your code in C++14 (g++ 6.2.0)
	std::vector<int> r;
	size_t right = 0;
	for (size_t i = 0; i < A.size(); ++i)
		right += A[i];
	int left = 0;
	for (size_t i = 0; i < A.size(); ++i) {
		if (left == right - A[i])
			return i;
		left += A[i];
		right -= A[i];
	}
	return -1;
}

int main() {
	std::vector<int> t = { -1, 3, -4, 5, 1, -6, 2, 1 };
	std::cout << solution(t) << std::endl;
  return 0;
}

