#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

int main(int ac, char* av[]) {
	if(ac >= 3){
		std::cout << "input file: " << av[1] << std::endl <<
			"output file: " << av[2] << std::endl;
		std::ifstream infile(av[1]);
		std::ofstream outfile(av[2], std::ofstream::binary);
		if(!infile.good()) {
			std::cout << "can`t open input file: " << av[1] << std::endl;
			return -1;	
		}
		if(!outfile.good()) {
			std::cout << "can`t open input file: " << av[2] << std::endl;
			return -1;	
		}
		std::for_each( std::istream_iterator<std::string>(infile),
			std::istream_iterator<std::string>(),
				[&outfile](const std::string& value) {
					std::cout << "convert : 0x" << value << " to: ";	
					unsigned int tmp = std::stoi(value, 0, 16);
					std::cout << tmp << std::endl;
					outfile.write(reinterpret_cast<const char*>(&tmp), 1);
				});
	
	}
	return 0;
}

