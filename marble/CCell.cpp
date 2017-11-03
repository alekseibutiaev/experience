/*
 * CCell.cpp
 *
 *  Created on: 19.08.2009
 *      Author: alexsy
 */

#include "CCell.h"

#include <string>
#include <iostream>

//******************************************************************************
CCell::CCell( int f_Border, int f_Value ) :
	pvValue( f_Value ), pvBorder( f_Border ) {
}
//******************************************************************************
CCell::~CCell() {
}
//******************************************************************************
int& CCell::Value() {
	return pvValue;
}
//******************************************************************************
int const& CCell::Value() const{
	return pvValue;
}
//******************************************************************************
int& CCell::Border() {
	return pvBorder;
}
//******************************************************************************
int const& CCell::Border() const {
	return pvBorder;
}
//******************************************************************************
bool CCell::IsNotEmpty() const{
	return pvValue ? true : false;
}
//******************************************************************************
void CCell::Print() const {

	std::string border;
	border += std::string( pvBorder & LeftBorder ? "L" : "_" );

	border += std::string( pvBorder & TopBorder ? "T" : "_" );
	border += std::string( pvBorder & RightBorder ? "R" : "_" );
	border += std::string( pvBorder & BottomBorder ? "B" : "_" );

/*	std::string status = std::string( pvStatus == StatusEmpty ? "E" :
		pvStatus == StatusBoll ? "B" : pvStatus == StatusHole ? "H" : "R" );*/

	std::cout << "Value = " << pvValue
		//<< " Status = " << status
		<< " Border = " << border << std::endl;

}

