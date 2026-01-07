/*
 * CRule.h
 *
 *  Created on: 24.08.2009
 *      Author: alexsy
 */

#ifndef CEDITORDER_H_
#define CEDITORDER_H_

#include <iostream>

enum Action{ Match = 0, Insert, Delete, Replace };

template < typename TYPE >
class CRule {

	template< typename TYPE1 >
	friend std::ostream& operator<< ( std::ostream& f_Stream,
			CRule< TYPE1 > const& f_Rule );

	template< typename TYPE1 >
	friend std::istream& operator>> ( std::istream& f_Stream,
			CRule< TYPE1 >& f_Rule );

	int pvAction;
	TYPE pvDataA;
	TYPE pvDataB;
public:
	CRule(){};
	CRule( int f_Action, TYPE const& f_DataA, TYPE const& f_DataB = TYPE() ) :
		pvAction( f_Action ), pvDataA( f_DataA ), pvDataB( f_DataB ) {
	}
	TYPE const& DataA() const {
		return pvDataA;
	};
	TYPE const& DataB() const {
		return pvDataB;
	}
	int const& Action() const{
		return pvAction;
	}
};
//******************************************************************************
template< typename TYPE >
std::ostream& operator<<( std::ostream& f_Stream,
		CRule< TYPE > const& f_Rule ) {
	std::string action = f_Rule.pvAction == Match ? " = " :
		f_Rule.pvAction == Replace ? " * " :
		f_Rule.pvAction == Delete ? " > " : " < ";
	f_Stream << f_Rule.pvDataA << action << f_Rule.pvDataB << std::endl;
	return f_Stream;
}
//******************************************************************************
template< typename TYPE >
std::istream& operator>>( std::istream& f_Stream,
			CRule< TYPE >& f_Rule ){
	std::string a;
	if( f_Stream.good() )
		f_Stream >> f_Rule.pvDataA;
	if( f_Stream.good() ){
		f_Stream >> a;
		std::cout << a << std::endl;
		f_Rule.pvAction = a == "=" ? Match : a == "*" ? Replace :
			a == ">" ? Delete : Insert;
		}
	if( f_Stream.good() ) {
		if( f_Rule.pvAction != Delete && f_Rule.pvAction != Insert )
			f_Stream >> f_Rule.pvDataB;
		else
			f_Rule.pvDataB = TYPE();
	}
	std::cout << f_Rule.pvDataA << a << f_Rule.pvDataB << std::endl;
	return f_Stream;
}

#endif /* CEDITORDER_H_ */
