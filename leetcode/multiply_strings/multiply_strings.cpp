#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


class Solution {
public:
	std::string multiply(std::string num1, std::string num2) {
		std::vector<std::string> strings;
		strings.reserve(num2.size());
		for (std::string::const_reverse_iterator it = num2.rbegin(); it != num2.rend(); ++it) {
			const std::size_t dist = it - num2.rbegin();
			strings.push_back(multiply(num1, *it) + std::string(dist,'0'));
		}
		correct_size(strings);
		std::string result = plus(strings);
		result.erase(0, result.find_first_not_of("0"));
		return result.empty() ? "0": result;
	}
private:
	std::string multiply(const std::string& value, const char value1) const {
		std::string result;
		result.reserve(value.size() * 2);
		int overload = 0;
		for( std::string::const_reverse_iterator it = value.rbegin(); it != value.rend(); ++it ) {
			const int tmp = (*it - '0') * (value1 - '0') + overload;
			result.insert(result.begin(), tmp % 10 + '0');
			overload = tmp / 10;
		}
		if(overload)
			result.insert(result.begin(), overload + '0');
		return result;
	}
	void correct_size(std::vector<std::string>& value) {
		std::size_t max = 0;
		for (std::size_t i = 0; i < value.size(); ++i)
			max = std::max(max, value[i].size());
		for (std::size_t i = 0; i < value.size(); ++i)
			if (std::size_t dist = max - value[i].size())
				value[i] = std::string(dist, '0') + value[i];

	}
	std::string plus(const std::vector<std::string>& value) {
		try{
			std::string result;
			int overload = 0;
			for(int i = static_cast<int>(value[0].size() - 1); i >= 0; --i) {
				const int tmp = std::accumulate(value.begin(), value.end(), overload, [i](const int overload, const std::string& value) {
					return overload + value.at(i) - '0';
				});
				result.insert(result.begin(), tmp % 10 + '0');
				overload = tmp / 10;
			}
			return overload ? static_cast<char>(overload + '0') + result : result;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		return std::string();
	}
};

int main()
{
	Solution s;
	std::cout << s.multiply("140", "721") << std::endl;
	std::cout << s.multiply("1234", "639") << std::endl;
	std::cout << s.multiply("985", "6541") << std::endl;
	return 0;
}

