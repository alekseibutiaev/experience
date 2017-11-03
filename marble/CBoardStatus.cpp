/*
 * CBoardStatus.cpp
 *
 *  Created on: 21.08.2009
 *      Author: alexsy
 */

#include "CBoardStatus.h"
//******************************************************************************
void CBoardStatus::pvFillLiftsSequenceFrom( int const& f_LiftBegin ){
	int backlift = f_LiftBegin == East ? West : f_LiftBegin == West ? East :
		f_LiftBegin == Nord ? South : Nord;
	int index = 0;
	for( int lift = East; lift < LiftsCount; ++lift ) {
		if( lift != backlift )
			pvLifts[ index++ ] = lift;
	}
	pvLifts[ index++ ] = backlift;
	pvLifts[ index++ ] = LiftsCount;
}
//******************************************************************************
bool CBoardStatus::pvPrepareCell( CCell& f_ToCell, CCell& f_FromCell,
		int f_Border ){
	// Check border & boll in the new cell & old cell keep bool
	if( !( f_ToCell.Border() & f_Border ) && f_FromCell.Value() > 0 ) {
		if( f_ToCell.Value() <= 0 ) {
			int value = f_ToCell.Value() + f_FromCell.Value();
			if( !value ) {
				// bool in the hole
				f_ToCell.Value() = 0;
				f_FromCell.Value() = 0;
			}
			if( value == f_FromCell.Value() ) {
				// boll on the new cell
				f_ToCell.Value() = f_FromCell.Value();
				f_FromCell.Value() = 0;
			}
			else
				// error the hole do not for this boll
				return false;
		}
	}
	return true;
}
//******************************************************************************
bool CBoardStatus::pvLiftEast() {
	for( int i = 0; i < Size(); ++i ) {
		for( int y = 0; y < Size(); ++y ) {
			for( int x = 1; x < Size(); ++x ) {
				CCell& newcell = ptCellAt( x - 1, y );
				CCell& oldcell = ptCellAt( x, y );
				if( !pvPrepareCell( newcell, oldcell, RightBorder ) )
					return false;
			}
		}
	}
	return true;
}
//******************************************************************************
bool CBoardStatus::pvLiftNord() {
	for( int i = 0; i < Size(); ++i ){
		for( int x = 0; x < Size(); ++x ) {
			for( int y = Size() - 2; y >= 0; --y ) {
				CCell& newcell = ptCellAt( x, y + 1 );
				CCell& oldcell = ptCellAt( x, y );
				if( !pvPrepareCell( newcell, oldcell, TopBorder ) )
					return false;
			}
		}
	}
	return true;
}
//******************************************************************************
bool CBoardStatus::pvLiftWest() {
	for( int i = 0; i < Size(); ++i ){
		for( int y = 0; y < Size(); ++y ) {
			for( int x = Size() - 2; x >=0 ; --x ) {
				CCell& newcell = ptCellAt( x + 1, y  );
				CCell& oldcell = ptCellAt( x, y );
				if( !pvPrepareCell( newcell, oldcell, LeftBorder ) )
					return false;
			}
		}
	}
	return true;
}
//******************************************************************************
bool CBoardStatus::pvLiftSouth() {
	for( int i = 0; i < Size(); ++i ){
		for( int x = 0; x < Size(); ++x ) {
			for( int y = 1; y < Size(); ++y ) {
				CCell& newcell = ptCellAt( x, y - 1  );
				CCell& oldcell = ptCellAt( x, y );
				if( !pvPrepareCell( newcell, oldcell, BottomBorder ) )
					return false;
			}
		}
	}
	return true;
}
//******************************************************************************
bool CBoardStatus::pvLift( int f_Side ) {
	switch( f_Side ) {
		case East:
			return pvLiftEast();
		case Nord:
			return pvLiftNord();
		case West:
			return pvLiftWest();
		case South:
			return pvLiftSouth();
		default :
			pvCurrentIndex = LiftsCount;
			return false;
	}
}
//******************************************************************************
CBoardStatus::CBoardStatus( CBoard const& f_Board, int const& f_Lift ) :
	CBoard( f_Board ), pvCurrentIndex( 0 ),	pvSide( 0 ) {
	pvFillLiftsSequenceFrom( f_Lift );
}
//******************************************************************************
CBoardStatus::~CBoardStatus() {
}
//******************************************************************************
bool CBoardStatus::AllCase(){
	return pvCurrentIndex >= LiftsCount;
}
//******************************************************************************
bool CBoardStatus::NextStatus() {
	return pvLift( pvLifts[ pvCurrentIndex++ ] );
}
//******************************************************************************
int const& CBoardStatus::Status() const  {
	return pvLifts[ pvCurrentIndex - 1 ];
}
//******************************************************************************
char CBoardStatus::SymbolOfState() const{
	int status = Status();
	return status == East ? 'E' : status == Nord ? 'N' : status == West ? 'W' :
		status == South ? 'S' : '*';

}
