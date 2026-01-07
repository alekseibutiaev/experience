#include <string>
#include <vector>
#include <iostream>

class Solution {
public:
	std::string convert(std::string s, int numRows) {
		if (numRows == 1)
			return s;
		std::vector<std::string> array(numRows, std::string());
		int aindex = 0;
		int direction = 1;
		for (unsigned int index = 0; index < s.size(); ++index ) {
			if(aindex == 0)
				direction = 1;
			if(aindex + 1 == numRows)
				direction = -1;
			array[aindex].push_back(s[index]);
			aindex += direction;
		}
		std::string result;
		for (int index = 0; index < numRows; ++index)
			result += array[index];
		return result;
	}
};

int main()
{
	Solution s;
	std::cout << s.convert( "PAYPALISHIRING", 3 ) << std::endl;
	std::cout << s.convert("AB", 1) << std::endl;
	return 0;
}

