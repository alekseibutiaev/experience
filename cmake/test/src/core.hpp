#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>

#include "types.hpp"
#include "common.hpp"

void print( const ints_t& value );

template< typename T, std::size_t N>
void print( const T(&value)[N] ) {
	std::copy( &value[0], &value[N], std::ostream_iterator<T>(std::cout, " ") );
	std::cout << std::endl;
}

