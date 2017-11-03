/*
 * CSolution.h
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#ifndef CSOLUTION_H_
#define CSOLUTION_H_

#include "CBoardStatus.h"
#include <list>
#include <utility>
#include <string>

typedef std::list< int > CLiftCounter;

typedef std::list< CBoardStatus > CStatusStack;

//******************************************************************************
class CSolution {
	CStatusStack pvStack;
	CLiftCounter pvLiftCounterFrom( int f_LiftBegin );
	bool pvExecute();
public:
	CSolution( CBoard const& f_Bord  );
	virtual ~CSolution();
	std::string Execute( int f_Case );
};

#endif /* CSOLUTION_H_ */
