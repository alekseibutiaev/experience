#include <string>
#include <iostream>

int main(int ac, char* av[]) {
	std::string tmp;
	for(;;) {
		std::cin >> tmp;
		if(!std::cin.good()) {
			std::cerr << "closed" << std::endl;
			return 0;
		}
		std::cout << tmp;
		std::cerr << "send" << std::endl; 
	}
	return 0;
}

