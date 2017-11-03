//******************************************************************************
// The Robocode project.
// The file of CDirection.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
//******************************************************************************

#include "CDirection.h"
#include "CRobocodeException.h"
#include "RobocodeTemplate.h"

// Define static of member of class a CDirection
CDirection::CDirectionTypeArray CDirection::pvDirectionType;
// The default constructor, for class a CDerection.
CDirection::CDirection() throw() : pvType( CDirection::RIGHT ) {
		pvInit();
};
// The copying constructor, for class a CDerection.
CDirection::CDirection( const CDirection& f_Direction ) throw() :
		pvType( f_Direction.pvType ) {
	pvInit();
};
// The assignmet operator, for class a CDirection.
CDirection& CDirection::operator=( const CDirection& f_Direction ) throw() {
	pvType = ( f_Direction.pvType );
	return *this;
}
// The addition operator, for class a CDirection
CDirection& CDirection::operator+( const CDirection& f_Direction ) throw() {
	CDirection::TYPE Type( f_Direction.DirectionType() );
	if( Type == CDirection::UP )
		pvType = ( pvType = pvType + CDirection::UP ) % CDirection::CIRCLE;
	else if( Type == CDirection::TOLEFT )
		pvType = ( pvType = pvType + CDirection::TOLEFT ) < 0 ? 
				CDirection::DOWN : pvType;
	else
		pvType = ( pvType + CDirection::LEFT ) % CDirection::CIRCLE;
	return *this;
}
// Getting a type of Direction.
CDirection::TYPE CDirection::DirectionType( ) const throw() {
	return pvType;
};
// To initialize the array type name.
void CDirection::pvInit() throw() {
	if( pvDirectionType.empty() ){
		pvDirectionType.push_back( CDirectionTypeName( "0", CDirection::RIGHT ) );
		pvDirectionType.push_back( CDirectionTypeName( "90", CDirection::UP ) );
		pvDirectionType.push_back( CDirectionTypeName( "-90", CDirection::TOLEFT ) );
		pvDirectionType.push_back( CDirectionTypeName( "180", CDirection::LEFT ) );
		pvDirectionType.push_back(CDirectionTypeName( "270", CDirection::DOWN ) );
		}
}
// operator >> for class a CDirection.
std::istream& operator>>(std::istream& f_is, CDirection& f_Direct ) {
	std::string temp;
	try{
		if( !( f_is >> temp ).fail() )
			f_Direct.pvType = GetType< CDirection::TYPE >( f_Direct.pvDirectionType,
					temp );
		}
	catch( CRobocodeException& err ) {
		std::cerr << err.What() << std::endl;
		f_is.clear( std::ios_base::failbit );
		}
	return f_is;
};
