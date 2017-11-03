#include <iostream>
#include <algorithm>
#include <iterator>

template<int N>
int incr(int(&A)[N]) {
	for (int index = N - 1; index >= 0 ;--index) {
		++A[index];
		if (A[index] > 9)
			A[index] = 0;
		else
			return 0;
	}
	return 1;
}

int main()
{
	int a[] = { 0, 0, 0 };
	int cr = incr(a);
	std::cout << cr;
	std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(std::cout, ""));
	std::cout << std::endl;
	return 0;
}

