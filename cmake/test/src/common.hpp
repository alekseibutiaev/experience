#pragma once

#include "types.hpp"

namespace std_cxx17 {

	template <typename T, std::size_t N>
	std::size_t size( const T(&)[N] ) { return N; }

}; /* namespace std_cxx17 */

