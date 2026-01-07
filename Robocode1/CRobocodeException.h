//******************************************************************************
// The Robocode project.
// The file of CRobocodeException.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CRobocodeException.h"
//******************************************************************************

#ifndef __CROBOCODEEXCEPTION_H__
#define __CROBOCODEEXCEPTION_H__

// The class Exception for project of Robocode.
class CRobocodeException {
	// The pointer to string of mistake.
	const char* pvWhat;
public:
	// The constructor for class a CRobocodeException.
	CRobocodeException( const char* f_What ) throw();
	// Getting messages about mistake.
	const char* What() throw();
};

#endif /*CROBOCODEEXCEPTION_H_*/
