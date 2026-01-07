//******************************************************************************
// The Robocode project.
// The file of CUnit.cpp
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
//******************************************************************************

#include "CUnit.h"

// The default constructor for class a CUnit.
CUnit::CUnit() throw() {
};
// The initialize constructor for class a CUnit
CUnit::CUnit( CIntPair f_IntPair, CDirection f_Direction, CUnit::TYPE f_Type,
		const std::string& f_Name ) throw() : CIntPair( f_IntPair ),
		CDirection( f_Direction ), pvType( f_Type ), pvName( f_Name ) {
};
// The copying constructor for class a CUnit.
CUnit::CUnit( const CUnit& f_Unit ) throw() : CIntPair( f_Unit ),
		CDirection( f_Unit ), pvType( f_Unit.pvType ), pvName( f_Unit.pvName ),
		pvQueueCommand( f_Unit.pvQueueCommand ){
};
// The assingmed operator for class a CUnit.
CUnit& CUnit::operator=( const CUnit& f_Unit ) throw() {
	static_cast< CIntPair& >( *this ) = f_Unit;
	static_cast< CDirection& >( *this ) = f_Unit;
	pvType = f_Unit.pvType;
	pvName = f_Unit.pvName;
	pvQueueCommand = f_Unit.pvQueueCommand;
	return *this;
};

void CUnit::AddCommand( const CCommand& f_Command ) throw() {
		pvQueueCommand.push( f_Command );
};
std::size_t CUnit::HaveCommand() const throw() {
	return pvQueueCommand.size();
};
// getting the name of unit
const std::string& CUnit::Name() const throw() {
	return pvName;
};
// getting the Type of unit
const CUnit::TYPE& CUnit::UnitType() const throw() {
	return pvType;
};
// The Action of CUnit
void CUnit::Action( CCommandManager& f_CommandManager ) throw() {
	if( !pvQueueCommand.empty() ){
		CCommand& Command( pvQueueCommand.front() );
		if( !f_CommandManager.Action( *this, Command ) && pvType ==
				CUnit::TANK )
			pvQueueCommand.pop();
		}
}
// The operator>> for class a CCommand.
std::istream& operator>>( std::istream& f_is, CUnit& f_Unit ){
	f_Unit.pvType = CUnit::TANK;
	CIntPair IntPair;
	if( !( f_is >> f_Unit.pvName).good() ){
		f_is.clear( std::ios_base::failbit );
		return f_is;
		}
	else if( ( f_is >> IntPair  ).fail() )
		return f_is;
	else
		f_is >> static_cast< CDirection& >( f_Unit );
	IntPair.first *= I_PIXEL_PER_SECOND / 10;
	IntPair.second *= I_PIXEL_PER_SECOND / 10;
	static_cast< CIntPair& >( f_Unit ) = IntPair;
	return f_is;
}
// Is Unit.
bool IsUnit( const std::string& f_String, CUnit& f_Unit ){
	std::istringstream ss( f_String );
	return ( ss >> f_Unit ).eof();
}
