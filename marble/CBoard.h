/*
 * CBoard.h
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#ifndef CBOARD_H_
#define CBOARD_H_

#include "CCell.h"

#include <vector>

//******************************************************************************
class CBoard {
	typedef std::vector<CCell> CCellArray;
	int pvSize;
	CCellArray pvCells;
	void ptBoardAround();
protected:
	void ptSetSize( int f_Size );
	CCell& ptCellAt( unsigned int f_X, unsigned int f_Y );
public:
	CBoard();
	virtual ~CBoard();
	int const& Size() const;
	CCell& CellAt( unsigned int f_X, unsigned int f_Y );
	bool Complete();
	bool operator==( CBoard const& f_Board ) const;
	void Show() const;
};

#endif /* CBOARD_H_ */
