//******************************************************************************
// The Robocode project.
// Programming by Butaev A.J.
//******************************************************************************
#include "CUnit.h"
#include "CCommand.h"
#include "CRobocodeException.h"
#include "CCommandManager.h"
#include "CReferee.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

// The main of function.
int main( int ac, char* av[] ){
	int result( 1 );
	std::ifstream infile;
	std::ofstream outfile;
	std::string temp;
	CUnit Unit;
	CCommand Command;
	std::auto_ptr< CReferee > Referee;
	try{
		Referee = std::auto_ptr< CReferee >( new CRobocodeReferee() );
		infile.open( av[ 1 ] );
		outfile.open( av[ 2 ] );
		if( !infile.good() || !outfile.good() )
			throw( CRobocodeException( "Can't opened file." ) );
		// read input file.
		while( !infile.eof() ){
			getline( infile, temp );
			temp = std::string( temp.begin(), std::remove_if( temp.begin(),
					temp.end(), static_cast< int(*)(int) >( iscntrl ) ) );
			// Try getting next game
			if( IsReferee( temp, *Referee ) ){
				std::string Winer;
				if( Referee->StartPeriod( Winer ) )
					outfile << Winer << std::endl;
				if( Referee->End() )
					break;
				}
			// Try getting next tank.
			else if( IsUnit( temp, Unit ) ){
				Referee->AddUnit( Unit );
				}
			// Try getting next command.
			else if( IsCommand( temp, Command ) ){
				Referee->AddCommand( Command );
				}
			else
				throw( CRobocodeException( "Unknown string" ) );
			}
		result = 0;
		}
	catch( CRobocodeException& err ) {
		std::cerr << err.What() << std::endl;
		}
	catch( std::bad_alloc ){
		std::cerr << "Can't create Refery object." << std::endl
		}
	catch( ... ) {
		std::cerr << "Unknown mistake." << std::endl ;
		}
	infile.close();
	outfile.close();
	return result;
}
