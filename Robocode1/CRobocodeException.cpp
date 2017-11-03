//******************************************************************************
// The Robocode project.
// The file of CRobocodeException.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
//******************************************************************************
#include "CRobocodeException.h"

// The constructor for class a CRobocodeException.
CRobocodeException::CRobocodeException( const char* f_What ) throw() :
	pvWhat( f_What ) {};
// Getting messages about mistake.
const char* CRobocodeException::What() throw() {
	return pvWhat;
};
