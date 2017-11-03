#include <string>
#include <iostream>

class Solution {
public:
	std::string longestPalindrome(std::string s) {
		if (1 == s.size())
			return s;
		std::string result;
		for (int index = 0; index < static_cast<int>(s.size()-1); ++index) {
			int ps;
			ps = palindromic(s, 1, index);
			if (0 < ps) {
				const std::string tmp = std::string(&s[index - ps], &s[index + 1 + ps]);
				if (result.size() < tmp.size())
					result = tmp;
			}
			ps = palindromic(s, 0, index, index + 1);
			if (0 <= ps) {
				const std::string tmp = std::string( &s[index - ps], &s[index + 2 + ps] );
				if (result.size() < tmp.size())
					result = tmp;
			}
		}
		return result.empty() ? std::string( &s[0], &s[1] ) : result;
	}
private:
	int palindromic( const std::string& value, int deep, const int middle ) {
		if( 0 > middle - deep || middle + deep >= value.size() || value[middle - deep] != value[middle + deep] )
			return --deep;
		return palindromic(value, ++deep, middle);
	}

	int palindromic(const std::string& value, int deep, const int left, const int right) {
		if( left - deep < 0 || right + deep >= value.size() || value[left - deep] != value[right + deep] )
			return --deep;
		return palindromic(value, ++deep, left, right);
	}
};

int main()
{
	Solution s;
	std::cout << s.longestPalindrome("aaaa") << std::endl;

#if 1
	std::cout << s.longestPalindrome("321123") << std::endl;
	std::cout << s.longestPalindrome("321123r") << std::endl;
	std::cout << s.longestPalindrome("x321123r") << std::endl;
	std::cout << s.longestPalindrome("x321123") << std::endl;
#endif
#if 1
	std::cout << s.longestPalindrome("32523") << std::endl;
	std::cout << s.longestPalindrome("d32523") << std::endl;
	std::cout << s.longestPalindrome("d32523r") << std::endl;
	std::cout << s.longestPalindrome("32523r") << std::endl;
#endif
	return 0;
}

