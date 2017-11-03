#include <iterator>

#include "types.hpp"
#include "common.hpp"
#include "core.hpp"

int main( int ac, char* av[] ) {

	int a0[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ints_t a1(std::begin(a0), std::end(a0));
	print(a0);
	print(a1);

	return 0;
}

