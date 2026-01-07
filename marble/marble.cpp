/*
 * marble.cpp
 *
 *  Created on: 19.08.2009
 *      Author: alexsy
 */

#include "CBoardInit.h"
#include "CSolution.h"

#include <iostream>
#include <fstream>
#include <string>

#define OUTPUT_NAME "Out.txt"

//******************************************************************************
int main( int ac, char* av[] ) {
	char const* inputname;
	char const* outputname = OUTPUT_NAME;
	int cases = 0;
	if( ac < 2 ) {
		std::cerr << "The input file do not given." << std::endl;
		return EXIT_FAILURE;
		}
	else if( ac >= 3 )
		outputname = av[2];
	inputname = av[1];
	std::ifstream input( inputname );
	std::ofstream output( outputname );

	do {
		CBoardInit board;
		do {
			std::string string;
			std::getline( input, string );
			if( board.InitBord( string ) )
				continue;
			if( board.SetMarble( string ) )
				continue;
			if( board.SetBorder( string ) )
				continue;
			} while( input.good() && !board.Complete() );
			if( board.Size() > 0 ) {
				CSolution solution( board );
				output << solution.Execute( ++cases ) << std::endl;
			}
		} while( input.good() );
	input.close();
	output.close();

	return EXIT_SUCCESS;
}
