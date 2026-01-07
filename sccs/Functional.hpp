/*
 * Levenshtein.hpp
 *
 *  Created on: 24.08.2009
 *      Author: alexsy
 */

#ifndef FUNCTIONAL_HPP_
#define FUNCTIONAL_HPP_

#include "CRule.h"

#include <vector>
#include <string>

#include <iostream>
#include <iterator>


//******************************************************************************
// generate rules
//******************************************************************************
template < typename TYPE >
void FillRuleSequence( std::vector< CRule< TYPE > >& f_OrderSequence,
		std::vector< TYPE > const& f_Col, std::vector< TYPE > const& f_Row ) {
	typename std::vector< CRule< TYPE > > ordersequence;

	std::vector< std::vector< int > > table	= std::vector< std::vector< int > >(
			f_Row.size() + 1, std::vector< int >( f_Col.size() + 1, 0 ) );

	std::size_t i ;
	for( i = 0; i < table.size(); ++i )
		table[i][0] = i;
	for( i = 0; i < table[0].size(); ++i )
		table[0][i] = i;
	table[0][0] = 0;
	// create table
	for( std::size_t row = 1; row <= f_Row.size(); ++row ) {
		for( std::size_t col = 1; col <= f_Col.size() ; ++col) {
			bool cost  = f_Col[ col - 1 ] != f_Row[ row - 1 ];
			table[row][col] = std::min(
					table[ row - 1 ][ col - 1 ] + cost,
					std::min( table[ row ][ col - 1 ] + 1,
							table[ row - 1 ][ col ] + 1 ) );
		}
	}
	// get rule
	std::cout << std::endl;
	std::size_t row = f_Row.size();
	std::size_t col = f_Col.size();
	while( row != 0 && col != 0 ) {
		if( table[ row ][ col -1 ] < table[ row - 1 ][ col ] ) {
			f_OrderSequence.insert( f_OrderSequence.begin(),
					CRule< TYPE >( Delete, f_Col[ col - 1 ] ) );
			--col;
		}
		else if( table[ row ][ col -1 ] > table[ row - 1 ][ col ] ) {
			f_OrderSequence.insert( f_OrderSequence.begin(),
					CRule< TYPE >( Insert, f_Row[ row - 1 ] ) );
			--row;
		}
		else{
				f_OrderSequence.insert( f_OrderSequence.begin(),
					CRule< TYPE >(
							f_Row[ row - 1 ] == f_Col[ col - 1 ] ? Match : Replace,
							f_Col[ col - 1 ] , f_Row[ row - 1 ] ) );
			--row;
			--col;
		}
	}
}
//******************************************************************************
template < typename TYPE >
bool ReplaceSequence( std::vector< TYPE >& f_Sequence,
		std::vector< TYPE > const& f_From, std::vector< TYPE > const& f_To ) {
	typedef typename std::vector< TYPE >::iterator CIter;
	typedef typename std::iterator_traits< CIter >::difference_type CDifference;

	CIter result = std::search( f_Sequence.begin(), f_Sequence.end(),
			f_From.begin(), f_From.end() );

	if( result != f_Sequence.end() ) {
		CIter to = result;
		CDifference diff = std::distance( f_From.begin(), f_From.end() );
		std::advance( to, diff );
		f_Sequence.erase( result, to );
		f_Sequence.insert( result, f_To.begin(), f_To.end() );
		return true;
	}
	else
		std::cerr << "The sequence for change is not found." << std::endl;

	return false;
}
//******************************************************************************
template < typename TYPE >
bool ApplyRuleSequence(
		std::vector< CRule< TYPE > > const& f_OrderSequence,
		std::vector< TYPE >& f_Sequence ) {

	std::vector<TYPE> from;
	std::vector<TYPE> to;

	typename std::vector< CRule< TYPE > >::const_iterator rule =
		f_OrderSequence.begin();
	bool rulecomplete = false;
	bool ruleaccumulate = false;
	while( rule != f_OrderSequence.end() ) {
		std::cout << *rule << std::endl;
		int action = rule->Action();
		switch( action ){
			case Delete:
				std::cout << rule->DataA() << std::endl;
				from.push_back( rule->DataA() );
				ruleaccumulate = true;
				break;
			case Insert:
				to.push_back( rule->DataA() );
				ruleaccumulate = true;
				break;
			case Replace:
				to.push_back( rule->DataB() );
				from.push_back( rule->DataA() );
				ruleaccumulate = true;
				break;
			case Match:
				to.push_back( rule->DataB() );
				from.push_back( rule->DataA() );
				if( ruleaccumulate ){
					rulecomplete = true;
					ruleaccumulate = false;
				}
				break;
			default :
				std::cerr << "Rule do not right" << action << std::endl;
				return false;
		}
		if( rulecomplete ) {
			// apple
			if( !ReplaceSequence( f_Sequence, from, to ) )
				return false;
			rulecomplete = false;
			from.clear();
			to.clear();
		}
		++rule;
	}
// apple tail
	if( !from.empty() || !to.empty() ) {
		if( !ReplaceSequence( f_Sequence, from, to ) )
			return false;
	}
	return true;
}

#endif /* FUNCTIONAL_HPP_ */
