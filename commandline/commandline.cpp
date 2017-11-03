#include <unistd.h>

#include <iostream>

int main(int ac, char* av[]) {
	char buf[10240];
	const char* pwd = getcwd(buf, 10240);
	std::cout << "path: " << pwd << std::endl;
	for(int i = 0; i < ac; ++i )
		std::cout << av[i] << std::endl;
	return 0;
}

