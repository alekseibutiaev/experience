#include <vector>
#include <string>
#include <cctype>
#include <iostream>

int solution(std::string &S) {
	// write your code in C++14 (g++ 6.2.0)
	std::vector<int> a;
	std::string q;
	for (size_t i = 0; i < S.size(); ++i) {

		if (std::isdigit( S[i] )) {
			a.push_back(std::stoi(std::string(1, S[i])));
		}
		else {
			if (S[i] == '+') {
				if (a.size() > 1) {
					int l = a.back();
					a.pop_back();
					a.back() = l + a.back();
				}
				else
					return -1;
			}
			else if (S[i] == '*') {
				if (a.size() > 1) {
					int l = a.back();
					a.pop_back();
					a.back() = l * a.back();
				}
				else
					return -1;
			}
			else
				return -1;
		}
	}
	return a.back();
}

int main()
{
	std::string s = "13+62*7+*";
	std::cout << solution(s) << std::endl;
	s = "11++";
	std::cout << solution(s) << std::endl;
	return 0;
}

