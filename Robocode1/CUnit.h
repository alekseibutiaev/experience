//******************************************************************************
// The Robocode project.
// The file of CUnit.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CUnit.h"
//******************************************************************************
#ifndef __CUNIT_H__
#define __CUNIT_H__
#include "CIntPair.h"
#include "CDirection.h"
#include "CCommand.h"
#include "CCommandManager.h"

#include <queue>

typedef std::queue< CCommand > CCommandQueue;
// 
class CUnit : public CIntPair, public CDirection {
public:
	enum TYPE{ TANK, BULLET };
	CUnit() throw();
	CUnit( CIntPair f_IntPair, CDirection f_Direction, CUnit::TYPE f_Type,
			const std::string& f_Name ) throw();
	CUnit( const CUnit& f_Unit ) throw();
	CUnit& operator=( const CUnit& f_Unit ) throw();
	void AddCommand( const CCommand& f_Command ) throw();
	std::size_t HaveCommand() const throw();
	const std::string& Name() const throw();
	const CUnit::TYPE& UnitType() const throw();
	void Action( CCommandManager& f_CommandManager ) throw();
private:
	friend std::istream& operator>>( std::istream& f_is, CUnit& f_Unit );
	CUnit::TYPE pvType;
	std::string pvName;
	CCommandQueue pvQueueCommand;
};
// The operator>> for class a CCommand.
std::istream& operator>>( std::istream& f_is, CUnit& f_Unit );
// Is Unit.
bool IsUnit( const std::string& f_String, CUnit& f_Unit );

#endif /*__CUNIT_H__*/
