#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <string>

class Solution {
public:
	std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
		std::map<std::string, std::vector<std::string>> r;
		for (std::vector<std::string>::const_iterator i = strs.begin(); i != strs.end(); ++i) {
			std::string tmp = *i;
			std::sort(tmp.begin(), tmp.end());
			r[tmp].push_back(*i);
		}
		std::vector<std::vector<std::string>> result;
		std::transform(r.begin(), r.end(), std::back_inserter(result), [](const std::pair<const std::string, std::vector<std::string> >& value) {
			return value.second;
		});
		return result;
	}
};

int main()
{
	Solution s;
	std::vector<std::string> value = { "eat", "tea", "tan", "ate", "nat", "bat" };
	std::vector<std::vector<std::string>> r = s.groupAnagrams(value);
}

