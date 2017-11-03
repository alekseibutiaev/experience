/*
 * CBoard.cpp
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#include "CBoard.h"

#include <iostream>
#include <algorithm>
#include <functional>

//******************************************************************************
void CBoard::ptBoardAround() {
	// set borber
	for( int y = 0; y < pvSize; ++y ) {
		for( int x = 0; x < pvSize; ++x ) {
			int border = NoneBorder;
			if( !y )
				border |= TopBorder;
			else if( y == pvSize - 1 )
				border |= BottomBorder;
			if( !x )
				border |= LeftBorder;
			else if( x == pvSize - 1 )
				border |= RightBorder;
			CellAt( x, y ).Border() = border;
		}
	}
}
//******************************************************************************
void CBoard::ptSetSize( int f_Size ) {
	pvSize = f_Size;
	pvCells = CCellArray( f_Size * f_Size );
	ptBoardAround();
}
//******************************************************************************
CCell& CBoard::ptCellAt( unsigned int f_X, unsigned int f_Y ) {
	return pvCells[ f_Y * pvSize + f_X ];
}
//******************************************************************************
CBoard::CBoard() : pvSize( 0 ) {
}
//******************************************************************************
CBoard::~CBoard() {
}
//******************************************************************************
CCell& CBoard::CellAt( unsigned int f_X, unsigned int f_Y ) {
	return pvCells[ f_Y * pvSize + f_X ];
}
//******************************************************************************
int const& CBoard::Size() const {
	return pvSize;
}
//******************************************************************************
bool CBoard::Complete() {
	return std::find_if( pvCells.begin(), pvCells.end(),
			std::mem_fun_ref( &CCell::IsNotEmpty ) ) == pvCells.end();
}
//******************************************************************************
bool CBoard::operator==( CBoard const& f_Board ) const {
	return pvSize == f_Board.pvSize && pvCells == f_Board.pvCells;
}
//******************************************************************************
void CBoard::Show() const {
	std::for_each( pvCells.begin(), pvCells.end(),
		std::mem_fun_ref( &CCell::Print ) );
	std::cout << std::endl;
}




