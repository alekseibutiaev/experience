//******************************************************************************
// The Robocode project.
// The file of CInitPair.cpp
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
//******************************************************************************
#include "CIntPair.h"

std::istream& operator>>( std::istream& f_is, CIntPair& f_IntPair ){
	if( !( f_is >> f_IntPair.first ).good() )
		f_is.clear( std::ios_base::failbit );
	else
		f_is >> f_IntPair.second;
	return f_is;
}
