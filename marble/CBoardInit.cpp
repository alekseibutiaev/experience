/*
 * CBoardInit.cpp
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#include "CBoardInit.h"

#include <iostream>
#include <sstream>
#include <iterator>

#define MARBLEPARAM_ELEMENTS 2
#define BORDPARAM_ELEMENTS 3
#define WALLPARAM_ELEMENTS 4

#define BORDSIZE_INDEX 0
#define MARBLESCOUNT_INDEX 1
#define WALLSCOUNT_INDEX 2

#define MARBLE_Y_INDEX 0
#define MARBLE_X_INDEX 1

#define WALLA_Y_INDEX 0
#define WALLA_X_INDEX 1
#define WALLB_Y_INDEX 2
#define WALLB_X_INDEX 3



//******************************************************************************
CBoardInit::CBoardInit() : pvMarblesCount( 0 ), pvWallsCount( 0 ),
	pvCurrentMarble( 0 ), pvCurrentWall( 0 ) {
}
//******************************************************************************
CBoardInit::~CBoardInit() {
}
//******************************************************************************
CBoardInit::CParamArray CBoardInit::pvParametrFromString(
		std::string const& f_String ){
	CParamArray result;
	std::stringstream ss( f_String );
	std::copy( std::istream_iterator< CParamArray::value_type >( ss ),
			std::istream_iterator< CParamArray::value_type >(),
			std::back_inserter( result ) );
	return result;
}
//******************************************************************************
bool CBoardInit::InitBord( std::string const& f_Param ) {
	CParamArray param = pvParametrFromString( f_Param );
	if( param.size() != BORDPARAM_ELEMENTS )
		return false;
	ptSetSize( param[ BORDSIZE_INDEX ] );
	pvMarblesCount = param[ MARBLESCOUNT_INDEX ];
	pvWallsCount = param[ WALLSCOUNT_INDEX ];
	pvCurrentMarble = 0;
	pvCurrentWall = 0;
	return true;
}
//******************************************************************************
bool CBoardInit::SetMarble( std::string const& f_Param ){
	CParamArray param = pvParametrFromString( f_Param );
	if( param.size() != MARBLEPARAM_ELEMENTS )
		return false;
	++pvCurrentMarble;
	int value = pvMarblesCount >= pvCurrentMarble ? pvCurrentMarble :
		pvMarblesCount - pvCurrentMarble;
	CellAt( param[ MARBLE_X_INDEX ], param[ MARBLE_Y_INDEX ] ).Value() = value;
	return true;
}
//******************************************************************************
bool CBoardInit::SetBorder( std::string const& f_Param ) {

	CParamArray param = pvParametrFromString( f_Param );
	if( param.size() != WALLPARAM_ELEMENTS )
		return false;

	int xa = param[ WALLA_X_INDEX ];
	int ya = param[ WALLA_Y_INDEX ];
	int xb = param[ WALLB_X_INDEX ];
	int yb = param[ WALLB_Y_INDEX ];

	CCell& cella = CellAt( xa, ya );
	CCell& cellb = CellAt( xb, yb );

	int diffx = xa - xb;
	int diffy = ya - yb;
	int bordera = cella.Border();
	int borderb = cellb.Border();

	if( abs( diffx ) == 1 && !diffy ) {
		if( diffx > 0 ) {
			bordera |= LeftBorder;
			borderb |= RightBorder;
		}
		else {
			bordera |= RightBorder;
			borderb |= LeftBorder;
		}
	}
	else if( abs( diffy ) == 1 || ! diffx ) {
		if( diffy > 0 ) {
			bordera |= TopBorder;
			borderb |= BottomBorder;
		}
		else {
			bordera |= BottomBorder;
			borderb |= TopBorder;
		}
	}
	else
		return false;

	cella.Border() = bordera;
	cellb.Border() = borderb;
	++pvCurrentWall;
	return true;
}
//******************************************************************************
bool CBoardInit::Complete(){
	return Size() > 0 && pvCurrentMarble / 2 == pvMarblesCount &&
		pvCurrentWall == pvWallsCount;
}
