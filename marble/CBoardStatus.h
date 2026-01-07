/*
 * CBoardStatus.h
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#ifndef CBOARDSTATUS_H_
#define CBOARDSTATUS_H_

#include "CBoard.h"

//******************************************************************************
class CBoardStatus: public CBoard {
	enum Lifts{ East, Nord, West, South, LiftsCount };
	int pvCurrentIndex;
	int pvLifts[ LiftsCount ];
	int pvSide;
	void pvFillLiftsSequenceFrom( int const& f_LiftBegin );
	bool pvPrepareCell( CCell& f_ToCell, CCell& f_FromCell, int f_Border );
	bool pvLiftEast();
	bool pvLiftNord();
	bool pvLiftWest();
	bool pvLiftSouth();
	bool pvLift( int f_Side );
public:
	CBoardStatus( CBoard const& f_Board, int const& f_Status = East );
	virtual ~CBoardStatus();
	bool AllCase();
	bool NextStatus();
	int const& Status() const;
	char SymbolOfState() const;

};

#endif /* CBOARDSIDE_H_ */
