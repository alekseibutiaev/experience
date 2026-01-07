//******************************************************************************
// The Robocode project.
// The file of CCommand.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CCommand.h"
//******************************************************************************
#ifndef __CCOMMAND_H__
#define __CCOMMAND_H__

#include "CDirection.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>

// Define class a command.
class CCommand{
public:
	// The type of connamd.
	enum TYPE{ MOVE, STOP, TURN, SHOOT, UNKNOWN };
	// The default constructor, for class a CCommand.
	CCommand() throw();
	// The initialize constructor, for class a CCommand.
	CCommand( CCommand::TYPE f_Type, int f_Time, CDirection f_Angle ) throw();
	// The copying constructor, for class a CCommand.
	CCommand( const CCommand& f_Command ) throw();
	// The assignmet operator, for class a CDirection.
	CCommand& operator=( const CCommand& f_Command ) throw();
	// To receive a name of object for which belongs given
	const std::string& To() const throw();
	// To use a command.
	int UseCommand( CCommand::TYPE& f_Type, CDirection& f_Angle ) throw();
	// Getting type of command.
	CCommand::TYPE CommandType() const throw();
private:
	CCommand::TYPE pvType;
	int pvTime;
	CDirection pvAngle;
	std::string pvTo;
	friend std::istream& operator>>( std::istream& f_is, CCommand& f_Cmd );
	typedef std::pair< std::string, CCommand::TYPE > CCommandTypeName;
	typedef std::vector< CCommandTypeName > CCommandTypeArray;
	static CCommandTypeArray pvCommandType;
	// To fill a type of command of array.
	void pvInit();
};
// The operator>> for class a CCommand.
std::istream& operator>>( std::istream& f_is, CCommand& f_Command );
// Is Command.
bool IsCommand( const std::string& f_String, CCommand& f_Command );

#endif /*__CCOMMAND_H__*/
