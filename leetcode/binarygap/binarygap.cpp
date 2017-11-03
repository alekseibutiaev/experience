#include <algorithm>
#include <iostream>

int solution(int N) {
	int res = 0;
	int count = 0;
	bool start = false;
	while ( N ) {
		if (N % 2) {
			if (count && start)
				res = std::max(res, count);
			start = true;
			count = 0;
		}
		else
			++count;
		N /= 2;
	}
	return res;
}

int main()
{
	std::cout << solution(6) << std::endl;
	std::cout << solution(328) << std::endl;
	std::cout << solution(16) << std::endl;
	std::cout << solution(1024) << std::endl;
	std::cout << solution(1024) << std::endl;
	std::cout << solution(1041) << std::endl;
	std::cout << solution(51712) << std::endl;

  return 0;
}

