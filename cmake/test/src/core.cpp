#include "core.hpp"

void print( const ints_t& value ) {
	std::copy( value.begin(), value.end(), std::ostream_iterator<int>(std::cout, " ") );
	std::cout << std::endl;
}

