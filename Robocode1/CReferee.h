//******************************************************************************
// The Robocode project.
// The file of CReferee.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CReferee.h"
//******************************************************************************
#ifndef __CREFEREE_H__
#define __CREFEREE_H__

#include "CIntPair.h"

class CRobocodeException;
// The next class is interface, for control a rule of game.
class CReferee : public CIntPair {
public:
	CReferee() throw() : CIntPair( -1, -1 ) {};
	virtual ~CReferee() {}
	virtual void AddUnit( CUnit& f_Unit ) throw( CRobocodeException ) = 0;
	virtual void AddBullet( CUnit& f_Unit ) throw( CRobocodeException ) = 0;
	virtual void AddCommand( const CCommand& f_Command )
			throw( CRobocodeException ) = 0;
	virtual bool StartPeriod( std::string& f_Winer ) = 0;
	virtual bool End() const throw() = 0;
};

// Is Referee.
bool IsReferee( const std::string& f_String, CReferee& f_Referee ){
	std::istringstream ss( f_String );
	return ( ss >> static_cast< CIntPair& >( f_Referee ) ).eof();
}

#endif /*__CREFEREE_H__*/
