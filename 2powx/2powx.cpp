#include <iostream>
#include <iomanip> 

int main(int ac, char* av[])
{
	unsigned long long i = 1;
	int count = 0;
	while(i) {
		std::cout << "VALUE" << std::setfill ('0') << std::setw (2) << count++ << '=' << i << std::endl;
		i *= 2;
	}
	return 0;
}

