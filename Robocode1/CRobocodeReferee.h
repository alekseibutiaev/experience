//******************************************************************************
// The Robocode project.
// The file of CRobocodeReferee.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CRobocodeReferee.h"
//******************************************************************************
#ifndef __CROBOCODEREFEREE_H__
#define __CROBOCODEREFEREE_H__

#include "CReferee.h"
#include <memory>

class CUnit;
class CRobocodeException;

/*
// To check up an output for limits of a battlefield.
class COutOfRange : public std::unary_function< CUnit , bool >{
public:
	bool operator()( CUnit& f_Unit ) throw();
};
//To check up hit.
class CHitTest : public std::binary_function< CUnit, CUnit, bool > {
public:
	bool operator()( const CUnit& f_First, const CUnit& f_Second ) const
};
*/
//The rule of Robocode game.
class CRobocodeReferee : public CReferee {
	// first - Count of unit on battlefielf. second - Count of command for Unit
	std::auto_ptr< CCommandManager > pvCommandManager;
	typedef std::vector< CUnit > CBattlefield;
	typedef CBattlefield::iterator CBattlefieldIterator;
	typedef std::pair< CBattlefieldIterator, CBattlefieldIterator > CHit;
	CBattlefield pvBattlefield;
	CBattlefield pvBullet;
public:
	// The default constructor for class a CRobocodeReferee.
	CRobocodeReferee() throw( CRobocodeException );
	// Additional tank on batelfield.
	void AddUnit( CUnit& f_Unit ) throw( CRobocodeException );
	// Additional bullet on batelfield.
	void AddBullet( CUnit& f_Unit ) throw( CRobocodeException );
	// Adittional bullet on batlefield
	void AddCommand( const CCommand& f_Command )
			throw( CRobocodeException );
	// To start battle
	bool StartPeriod( std::string& f_Winer );
	bool End() const throw();
};

#endif /*__CROBOCODEREFEREE_H__*/
