/*
 * sccs.cpp
 *
 *  Created on: 22.08.2009
 *      Author: alexsy
 */

#include "Functional.hpp"
#include "CRule.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <climits>


//******************************************************************************
void show( std::vector< int > const& f_Row ) {
	std::copy( f_Row.begin(), f_Row.end(),
		std::ostream_iterator< int >( std::cout, " " ) );
std::cout << std::endl;

}
//******************************************************************************
template < typename TYPE >
bool readrules( typename std::vector< CRule< TYPE > >& f_Rules,
		char const* f_Filename ) {
	std::ifstream file( f_Filename );
	if( !file.good() )
		return false;
#if 1

	std::copy( std::istream_iterator< CRule< TYPE > >( file ),
			std::istream_iterator< CRule< TYPE > >(),
			std::back_inserter( f_Rules ) );
#endif
	return file.eof();
}
//******************************************************************************
template < typename TYPE >
bool readfile( std::vector< TYPE >& f_Sequence, char const* f_Filename ) {
	std::ifstream file( f_Filename );
	if( !file.good() )
		return false;
	std::copy( std::istream_iterator< TYPE >( file ),
			std::istream_iterator< TYPE >(),
			std::back_inserter( f_Sequence ) );
	return file.eof();
}
//******************************************************************************
void usage(){
	std::cerr << "Ussage: " << std::endl <<
		"sccs.exe input_file_1 input_file_2 changeset_file" << std::endl <<
		"or" << std::endl <<
		"sccs.exe input_file output_file changeset_file /apply" << std::endl;
}
//******************************************************************************
int main( int ac, char* av[] ){

	if( ac == 4 ) {
		// create chang set
		std::cout << av[1] << " " << av[2] << " " << av[ 3 ] << std::endl;
		std::vector< CRule< std::string > > rulesequence;
		std::vector< std::string > a;
		std::vector< std::string > b;
		if( !readfile( a, av[1] ) || !readfile( b, av[2] ) ) {
			std::cerr << "Can not reading input files." << std::endl;
			return EXIT_FAILURE;
		}
		FillRuleSequence( rulesequence, a, b );
		std::ofstream out( av[ 3 ] );
		std::copy( rulesequence.begin(), rulesequence.end(),
				std::ostream_iterator< CRule< std::string > >( out ));
		}
	else if( ac == 5 ) {
		// apply changset
		std::cout << av[4] << std::endl;
		if( !strcmp( av[4], "/apply" ) ) {
			// Apply changset
			std::vector< CRule< std::string > > rules;
			std::vector< std::string > input;
			if( !readfile( input, av[1] ) ) {
				std::cerr << "Can not reading input file." << std::endl;
				return EXIT_FAILURE;
			}
			if( !readrules( rules, av[3] ) ){
				std::cerr << "Can not reading file of rules." << std::endl;
				return EXIT_FAILURE;
			}
			if( ApplyRuleSequence< std::string >( rules, input ) ) {
				std::ofstream file( av[2] );
				if( file )
					std::copy( input.begin(), input.end(),
										std::ostream_iterator< std::string >( file, "\n" ) );
				else
					std::cerr << "Can not write data to file." << std::endl;
			}
		}
		else{
			usage();
			return EXIT_FAILURE;
		}
	}
	else {
		usage();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
