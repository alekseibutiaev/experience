//******************************************************************************
// The Robocode project.
// The file of RobocodeAlgorithm.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "RobocodeAlgorithm.h"
//******************************************************************************
#ifndef __ROBOCODEALGORITHM_H__
#define __ROBOCODEALGORITHM_H__

// The next algorithm to find pair of equal elements
// first, last: Input iterators to the initial and final positions in a sequence.
// pred : Binary predicate taking two elements as argument,
// and returning the result of the comparison between them.
// Return value: A pair, where its members first and second equal elements.
template < typename Iterator, typename BinaryPredicate >
std::pair< Iterator, Iterator > find_equal( Iterator begin, Iterator end,
		BinaryPredicate pred ) {
	Iterator second( begin );
	while( begin != end ){
		second = begin;
		while( ++second != end ){
			if( pred( *begin, *second ) )
				return make_pair( begin, second );
			}
		++begin;
		}
	return make_pair( begin, second );
}

#endif /*__ROBOCODEALGORITHM_H__*/
