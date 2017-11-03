//******************************************************************************
// The Robocode project.
// The file of CInitPair.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CInitPair.h"
//******************************************************************************
#ifndef __CINITPAIR_H__
#define __CINITPAIR_H__

#include <iostream>

// CIntPair. The pair from integer
typedef std::pair< int, int > CIntPair;
// the operator >> for class a CIntPair
std::istream& operator>>( std::istream& f_is, CIntPair& f_IntPair );

#endif /*__CINITPAIR_H__*/
