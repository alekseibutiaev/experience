#include <iostream>
#include <functional>

class Solution {
public:
	double myPow(double x, int n) {
		double result = 1.0;
		bool munus = 0 > n;
		if(munus)
			n *= -1;
		int _n = 0;
		int count = 0;
		while (n) {
			_n *= 2;
			if (n % 2)
				++_n;
			n /= 2;
			++count;
		}
		while (count--) {
			if (_n % 2)
				result *= x;
			if( _n != 1 )
			 result *= result;
			_n /= 2;
		}
		if (munus)
			result = 1.0 / result;
		return result;
	}
};

int main()
{
	Solution s;
	std::cout << std::fixed << s.myPow(21, 13) << std::endl;
	std::cout << std::fixed << s.myPow(3.89707, 2) << std::endl;

	return 0;
}
