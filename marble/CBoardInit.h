/*
 * CBoardInit.h
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#ifndef CBOARDINIT_H_
#define CBOARDINIT_H_

#include "CBoard.h"

#include <string>
//******************************************************************************
class CBoardInit: public CBoard {
	typedef std::vector< int > CParamArray;
	CParamArray pvParametrFromString( std::string const& f_String );
	int pvMarblesCount;
	int pvWallsCount;
	int pvCurrentMarble;
	int pvCurrentWall;
public:
	CBoardInit();
	virtual ~CBoardInit();
	bool InitBord( std::string const& f_Param );
	bool SetMarble( std::string const& f_Param );
	bool SetBorder( std::string const& f_Param );
	bool Complete();
};

#endif /* CBOARDINIT_H_ */
