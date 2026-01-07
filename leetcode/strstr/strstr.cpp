#include <string>
#include <iostream>

class Solution {
public:
	int strStr(std::string haystack, std::string needle) {
		if (needle.begin() == needle.end())
			return 0;
		std::string::const_iterator start = haystack.begin();
		while (start != haystack.end())
		{
			std::string::const_iterator it1 = start;
			std::string::const_iterator it2 = needle.begin();
			while ( *it1 == *it2 ) {
				++it1; ++it2;
				if( it2 == needle.end() )
					return static_cast<int>( it1 - haystack.begin() - needle.size());
				if( it1 == haystack.end() )
					return -1;
			}
			++start;
		}
		return -1;
	}
};

int main()
{
	Solution s;
	std::cout << s.strStr( "Binary function that accepts two elements as arguments", "accepts" ) << std::endl;
  return 0;
}

