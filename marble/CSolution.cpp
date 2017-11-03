/*
 * CSolution.cpp
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#include "CSolution.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cstdio>

//******************************************************************************
class CLoopTest {
	CBoard const& pvBoard;
public:
	CLoopTest( CBoard const& f_Board ) : pvBoard( f_Board ) {
	}
	bool operator()( CBoardStatus const& f_BoardStatus ) const {
		return pvBoard == f_BoardStatus;
	}
};
//******************************************************************************
bool CSolution::pvExecute() {
	// get reference to board on the top of stack
	CBoardStatus& previous = pvStack.back();
	// create new board and push to top of stack
	pvStack.push_back( CBoardStatus( previous, previous.Status() ) );
	// get reference to new board on the top of stack
	CBoardStatus& current = pvStack.back();
	while( !current.AllCase() ) {
		if( current.Complete() ) {
			pvStack.pop_back();
			return true;
			}
		// Change current board && compare with previous board;
		if( current.NextStatus() && !( current == previous ) ) {
			// Check loop without last element;
			CStatusStack::iterator last = --pvStack.end();
			if( std::find_if( pvStack.begin(), last, CLoopTest( current ) ) != last ) {
				pvStack.pop_back();
				return false;
				}
			if( pvExecute() )
				return true;
		}
	}
	pvStack.pop_back();
	return false;
}
//******************************************************************************
CSolution::CSolution( CBoard const& f_Board ) {
	pvStack.push_back( CBoardStatus( f_Board ) );
}
//******************************************************************************
CSolution::~CSolution() {
}
//******************************************************************************
std::string CSolution::Execute( int f_Case ) {
	std::ostringstream stream;
	stream << "Case " << f_Case << ": ";
	if( pvExecute() ) {
		stream << pvStack.size() - 1 << " movies ";
		std::transform( ++pvStack.begin(), pvStack.end(),
				std::ostream_iterator<char>( stream, ""),
				std::mem_fun_ref( &CBoardStatus::SymbolOfState ) );
		}
	else
		stream << "Impossible";
	stream << std::endl;
	std::cout << stream.str();
	return stream.str();
}
