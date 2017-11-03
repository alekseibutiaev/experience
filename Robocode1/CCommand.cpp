//******************************************************************************
// The Robocode project.
// The file of CCommand.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
//******************************************************************************

#include "const.h"
#include "CCommand.h"
#include "CRobocodeException.h"
#include "RobocodeTemplate.h"

#include <sstream>

// Define class a command.
CCommand::CCommandTypeArray CCommand::pvCommandType;
// The default constructor, for class a CCommand.
CCommand::CCommand() throw() : pvType( CCommand::UNKNOWN ), pvTime( 0 ),
	pvAngle(), pvTo() {
	pvInit();
};
// The initialize constructor, for class a CCommand.
CCommand::CCommand( CCommand::TYPE f_Type, int f_Time, CDirection f_Angle )
		throw() : pvType( f_Type ), pvTime( f_Time * I_PIXEL_PER_SECOND / 10 ),
		pvAngle( f_Angle ), pvTo() {
	pvInit();
};
// The copying constructor, for class a CCommand.
CCommand::CCommand( const CCommand& f_Command ) throw() :
		pvType( f_Command.pvType ), pvTime( f_Command.pvTime ),
		pvAngle( f_Command.pvAngle ), pvTo( f_Command.pvTo ) {
	pvInit();
};
// The assignmet operator, for class a CDirection.
CCommand& CCommand::operator=( const CCommand& f_Command ) throw() {
	pvType = f_Command.pvType;
	pvTime = f_Command.pvTime;
	pvAngle = f_Command.pvAngle;
	pvTo = f_Command.pvTo;
	return *this;
};
// To receive a name of object for which belongs given.
const std::string& CCommand::To() const throw() {
	return pvTo;
};
// To use a command
int CCommand::UseCommand( CCommand::TYPE& f_Type, CDirection& f_Angle ) throw(){
	f_Type = pvType;
	f_Angle = pvAngle;
	return pvTime--;
};
// Getting type of command.
CCommand::TYPE CCommand::CommandType() const throw() {
	return pvType;
};
// To fill a type of command of array.
void CCommand::pvInit() {
	if( pvCommandType.empty() ){
		pvCommandType.push_back( CCommandTypeName( "MOVE", CCommand::MOVE ) );
		pvCommandType.push_back( CCommandTypeName( "STOP", CCommand::STOP ) );
		pvCommandType.push_back( CCommandTypeName( "TURN", CCommand::TURN ) );
		pvCommandType.push_back( CCommandTypeName( "SHOOT", CCommand::SHOOT ) );
	}
}
// The operator>> for class a CCommand.
std::istream& operator>>( std::istream& f_is, CCommand& f_Command ){
	std::string type;
	int time;
	if( ( f_is >> time ).fail() )
		return f_is;
	else if( ( f_is >> f_Command.pvTo ).fail() )
		return f_is;
	else if( ( f_is >> type ).fail() )
		return f_is;
	else {
		try {
			f_Command.pvType = GetType< CCommand::TYPE >( f_Command.pvCommandType,
					type );
			}
		catch( CRobocodeException& err ){
			std::cerr << err.What() << std::endl;
			f_is.clear( std::ios_base::failbit );
			return f_is;
			}
		}
	if( f_Command.pvType == CCommand::TURN || f_is.good() )
		f_is >> f_Command.pvAngle;
	f_Command.pvTime = time * I_PIXEL_PER_SECOND;
	return f_is;
};
// Is Command.
bool IsCommand( const std::string& f_String, CCommand& f_Command ){
	std::istringstream ss( f_String );
	return ( ss >> f_Command ).eof();
}
