#include <iostream>
#include <atomic>

int main(int ac, char* av[]) {
	unsigned int rpos = 0xfffffffe;
	unsigned int wpos = 0x2;
	std::cout << wpos - rpos << std::endl;

	std::atomic<unsigned int> rposa(0xffffffff);
	std::atomic<unsigned int> wposa(0x0);
	std::cout << wposa - rposa << std::endl;

	return 0;
}

