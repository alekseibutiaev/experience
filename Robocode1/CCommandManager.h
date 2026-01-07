//******************************************************************************
// The Robocode project.
// The file of CCommandManager.h
// Programmer Butaev A.J.
// Version 0.1
// started: 20.10.2007
// #include "CCommandManager.h"
//******************************************************************************
#ifndef __CCOMMANDMANAGER_H__
#define __CCOMMANDMANAGER_H__

class CUnit;
class CCommand;

// The next class a visitor. for use command.
class CCommandManager {
public:
	virtual ~CCommandManager(){}
	virtual int Action( CUnit& f_Unit, CCommand& f_Command ) = 0;
};

#endif /*__CCOMMANDMANAGER_H__*/
