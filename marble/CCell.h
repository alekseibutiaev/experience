/*
 * CCell.h
 *
 *  Created on: 19.08.2009
 *      Author: alexsy
 */

#ifndef CCELL_H_
#define CCELL_H_

//******************************************************************************
enum CBorder { NoneBorder = 0x00, LeftBorder = 0x01, TopBorder = 0x02,
			RightBorder = 0x04, BottomBorder = 0x08,
			MaskBorder = LeftBorder | TopBorder | RightBorder | BottomBorder
};
//******************************************************************************
enum CCellStatus { StatusEmpty, StatusBoll,  StatusHole, StatusError };
//******************************************************************************
class CCell {
	int pvValue;
  int pvBorder;
public:
	CCell( int f_Border = NoneBorder,	int f_Value = 0 );
	~CCell();
	int& Value();
  int& Border();
	int const& Value() const;
	int const& Border() const;
	bool IsNotEmpty() const;
	bool operator==( CCell const& f_Cell ) const {
		return pvValue == f_Cell.pvValue && pvBorder == f_Cell.pvBorder;
	}
	void Print() const ;
};

#endif /* CCELL_H_ */
