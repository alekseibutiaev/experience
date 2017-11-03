#include <iostream>
#include <sstream>
#include <string>

std::string encode(const std::string & input)
{
	// Replace with your encoder here
	std::string res;
	if (input.empty()) return std::string();
	int count = 1;
	char p = input[0];
	for (std::size_t i = 1; i < input.size(); ++i) {
		if (p != input[i]) {
			if (count > 1 ) {
				res += std::to_string(count) + p;
				count = 0;
			}
			else
				res += p;
			p = input[i];
		}
		else
			++count;
	}
	if (count > 1)
		res += std::to_string(count) + p;
	else
		res += p;
	return res;
}



// "^@f2o" == encode("foo")

int main()
{
	std::cout << "Encoding  = " << encode("") << ", expected " << std::endl;
	std::cout << "Encoding foo = " << encode("foo") << ", expected f2o" << std::endl;
	std::cout << "Encoding foooooooooooo = " << encode("foooooooooooo") << ", expected f12o" << std::endl;
	std::cout << "Encoding bar = " << encode("bar") << ", expected bar" << std::endl;

	return 0;
}

//code style
//http ://github.com/bloomberg/BDE