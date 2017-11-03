//******************************************************************************
// The Robocode project.
// The file of CDirection.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CDirection.h"
//******************************************************************************
#ifndef __CDIRECTION_H___
#define __CDIRECTION_H___

#include <iostream>
#include <string>
#include <vector>
#include <utility>

// To define class of CDirection;
class CDirection {
public:
	// Define a type of the Direction.
	enum TYPE{ RIGHT = 0, UP = 90, LEFT = 180, DOWN = 270, CIRCLE = 360,
			TOLEFT = -90 };
	// The default constructor, for class a CDerection.
	CDirection() throw();
	// The copying constructor, for class a CDerection.
	CDirection( const CDirection& f_Direction ) throw();
	// The assignmet operator, for class a CDirection.
	CDirection& operator=( const CDirection& f_Direction ) throw();
	// The addition operator, for class a CDirection
	CDirection& operator+( const CDirection& f_Direction ) throw();
	// Getting a type of Direction.
	CDirection::TYPE DirectionType() const throw();
private:
	friend std::istream& operator>>( std::istream& f_is, CDirection& f_Direction );
	CDirection::TYPE pvType;
	typedef std::pair< std::string, CDirection::TYPE >
			CDirectionTypeName;
	typedef std::vector< CDirectionTypeName > CDirectionTypeArray;
	static CDirectionTypeArray pvDirectionType;
	// To initialize the array type name.
	void pvInit() throw();
};
// operator >> for class a CDirection
std::istream& operator>>(std::istream& f_is, CDirection& f_Direct );

#endif /*CDIRECTION_H_*/
