//******************************************************************************
// The Robocode project.
// The file of CRobocodeReferee.cpp
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
//******************************************************************************
#ifndef __CROBOCODEREFEREE_H__
#define __CROBOCODEREFEREE_H__

#include "const.h"
#include "CRobocodeReferee.h"
#include "CRobocodeException.h"
#include "CUnit.h"
#if 0
// To check up an output for limits of a battlefield.
bool COutOfRange::operator()( CUnit& f_Unit ) throw() {
	if( f_Unit.UnitType() == CUnit::TANK ) {
		f_Unit.first = f_Unit.first > I_BATTLEFIELD_WIDTH ?
				I_BATTLEFIELD_WIDTH : f_Unit.first < 0 ? 0 : f_Unit.first;
		f_Unit.second = f_Unit.second > I_BATTLEFIELD_HEIGHT ?
				I_BATTLEFIELD_HEIGHT : f_Unit.second < 0 ? 0 : f_Unit.second;
		return false;
		}
	else {
		if( f_Unit.first < 0 || f_Unit.first > I_BATTLEFIELD_WIDTH )
			return true;
		else if( f_Unit.second < 0 || f_Unit.second > I_BATTLEFIELD_HEIGHT )
			return true;
		else
			return false;
		}
};
//To check up hit.
class CHitTest : public std::binary_function< CUnit, CUnit, bool >{
public:
	bool operator()( const CUnit& f_First, const CUnit& f_Second ) const {
		return f_First.Name() != f_Second.Name() && 
				static_cast< const CIntPair& >( f_First ) ==
				static_cast< const CIntPair& >( f_Second );
		}
};
#endif
// The default constructor for class a CRobocodeReferee.
CRobocodeReferee::CRobocodeReferee() throw( CRobocodeException ) {
	try{
		pvCommandManager = std::auto_ptr< CCommandManager >(
				new CRobocodeCommandManager( *this ) );
		}
	catch( std::bad_alloc ){
		throw( CRobocodeException( "Can`t create a Referee class." ) );
		}
}
// Additional tank on batelfield.
void CRobocodeReferee::AddUnit( CUnit& f_Unit ) throw( CRobocodeException ) {
	if( pvBattlefield.size() >= static_cast< std::size_t >( first ) )
		throw( CRobocodeException( "The limit of tanks is exceeded" ) );
	pvBattlefield.push_back( f_Unit );
	};
// Additional bullet on batelfield.
void CRobocodeReferee::AddBullet( CUnit& f_Unit ) throw( CRobocodeException ){
	pvBullet.push_back( f_Unit );
}
// Adittional bullet on batlefield.
void CRobocodeReferee::AddCommand( const CCommand& f_Command )
		throw( CRobocodeException ) {
	// As the index on the end is used twice. We create a variable.
	CBattlefieldIterator End( pvBattlefield.end() );
	// to find tank by name
	CBattlefieldIterator Tank( std::find_if( pvBattlefield.begin(), End,
			std::bind2nd( CFindUnitByName(), f_Command.To() ) ) );
	if( Tank == End )
		throw( CRobocodeException( "The tank for which belongs a command"
					" is not found" ) );
	if( Tank->HaveCommand() >= static_cast< std::size_t >( second ) )
		throw( CRobocodeException( "The limit of command is exceeded" ) );
	Tank->AddCommand( f_Command );
}
// To start battle
bool CRobocodeReferee::StartPeriod( std::string& f_Winer ) {
	if( !pvBattlefield.size() )
		return false;
	CUnit::TYPE BulletType( CUnit::BULLET );
	while( true ) {
		if( pvBattlefield.empty() ){
			f_Winer = STING_NO_WINNER;
			break;
			}
		if( pvBattlefield.size() == 1 &&
				pvBattlefield.front().UnitType() == CUnit::TANK ){
			f_Winer = pvBattlefield.front().Name();
			break;
			}
// To check up presence of commands at unit being on a battlefield and
// To check up presence bullet on the battlefield.;
		if( std::find_if( pvBattlefield.begin(), pvBattlefield.end(),
					std::mem_fun_ref( &CUnit::HaveCommand ) ) == pvBattlefield.end()
					&& std::find_if( pvBattlefield.begin(), pvBattlefield.end(),
					std::bind2nd( CFindUnitByType(), BulletType ) ) ==
					pvBattlefield.end() ){
			f_Winer = STING_NO_WINNER;
			break;
			}
// One second in game
		for( int loop = 0; loop < I_PIXEL_PER_SECOND; ++loop ){
// To make action of each unit
			for( CBattlefieldIterator UnitPtr( pvBattlefield.begin() );
					UnitPtr != pvBattlefield.end(); ++UnitPtr )
			UnitPtr->Action( *pvCommandManager );
// To check a have new bullet.
			if( !pvBullet.empty() ){
				pvBattlefield.insert( pvBattlefield.end(), pvBullet.begin(),
						pvBullet.end() );
				pvBullet.clear();
				}
// To check position of unit and remove bullet outside.
				pvBattlefield.erase( remove_if( pvBattlefield.begin(),
						pvBattlefield.end(), CRobocodeReferee::COutOfRange() ),
						pvBattlefield.end() );
// To check hit heppenes
			bool loop( true );
			while( loop ){
				CHit Hit( find_equal( pvBattlefield.begin(), pvBattlefield.end(),
						CRobocodeReferee::CHitTest() ) );
				if( ( loop = Hit.first != Hit.second ) ){
// To remove the collided objects
					pvBattlefield.erase( Hit.first );
					pvBattlefield.erase( Hit.second );
					}
				}
			}
		}
// To clear of battlefield/ for next game.
	pvBattlefield.clear();
	return true;
};

bool CRobocodeReferee::End() const throw() {
	return !static_cast< bool >( first || second );
};

#endif /*__CROBOCODEREFEREE_H__*/
