//============================================================================
// Name        : multmatrix.cpp
// Author      : Butyaev A.J.
// Version     : 0.1
// Copyright   : GPLv2
// Description : Multiplication of matrix in C++, Ansi-style
//============================================================================

#include <vector>
#include <climits>
#include <utility>
#include <numeric>
#include <sstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <algorithm>

typedef std::vector< float > CRow;
typedef std::vector< CRow > CRowArray;
typedef std::back_insert_iterator< CRow > CInsert;
// UTF-8
// Можно Было использовать пример класса Matrix из
// ( Язык програмирования С++ 3е издание. Бьёрн Страуструп )
// Но списывать не хотелось

//*****************************************************************************
// Class Matrix
//*****************************************************************************
class CMatrix{
	CRowArray pvRowArray;
	class CColumnIndex{
		size_t pvColumnNumber;
	public:
		CColumnIndex( size_t f_ColumnNumber ) : pvColumnNumber( f_ColumnNumber ) {}
		const CRow::value_type& operator()( const CRow& f_Row ){
			return f_Row[ pvColumnNumber ];
			}
	};
public:
	friend std::istream& operator>>( std::istream& f_in, CMatrix& f_Matrix );
	friend std::ostream& operator<<( std::ostream& f_out, CMatrix& f_Matrix );
	friend CMatrix operator*( const CMatrix& f_A, const CMatrix& f_B );
	CMatrix(){};
	CMatrix( const CMatrix& f_Matrix ) : pvRowArray( f_Matrix.pvRowArray ) {};
	CMatrix& operator=( const CMatrix& f_Matrix ){
		pvRowArray = f_Matrix.pvRowArray;
		return *this;
	}
	unsigned int Column() const { return pvRowArray[0].size(); };
	unsigned int Row() const { return pvRowArray.size(); };
	void Transpose() {
		CRowArray rowarray;
		for( size_t column = 0; column < Column(); ++column ){
			CRow row;
			std::transform( pvRowArray.begin(), pvRowArray.end(),
					CInsert( row ), CColumnIndex( column ) );
			rowarray.push_back( row );
			}
		pvRowArray = rowarray;
	}

};
//*****************************************************************************
//*****************************************************************************
std::istream& operator>>( std::istream& f_in, CMatrix& f_Matrix ){
	size_t Width( UINT_MAX );
	size_t Height( UINT_MAX );
	std::string string;
	getline( f_in, string );
	if( !f_in.good() )
		return f_in;
	std::istringstream istring( string );
	istring >> Width >> Height;
	f_in.setstate( ( !istring.eof() || istring.good() ) ? std::ios_base::failbit :
			f_in.rdstate() );
	while( f_in.good() ){
		getline( f_in, string );
		if( ( !f_in.good() && !f_in.eof() ) || string == "" )
			break;
		CRow row;
		istring.clear();
		istring.str( string );
		std::copy( std::istream_iterator< CRow::value_type >( istring ),
				std::istream_iterator< CRow::value_type >(), CInsert( row ) );
		if( row.size() != Width )
			break;
		f_Matrix.pvRowArray.push_back( row );
	}
	f_in.setstate( f_Matrix.pvRowArray.size() != Height ? std::ios_base::failbit :
			f_in.rdstate() );
	return f_in;
}
//*****************************************************************************
//*****************************************************************************
std::ostream& operator<<( std::ostream& f_out, CMatrix& f_Matrix ){
	for( CRowArray::iterator i( f_Matrix.pvRowArray.begin() );
			i != f_Matrix.pvRowArray.end(); ++i ){
		std::copy( i->begin(), i->end(),
				std::ostream_iterator< CRow::value_type >( std::cout, " " ) );
		std::cout << std::endl;
		}
	return f_out;
}
//*****************************************************************************
//*****************************************************************************
CMatrix operator*( const CMatrix& f_multipliersA,
		const CMatrix& f_multipliersB ) {
	CMatrix result;
	CMatrix multipliersB( f_multipliersB );
	multipliersB.Transpose();
	for( CRowArray::const_iterator irown( f_multipliersA.pvRowArray.begin() );
			irown != f_multipliersA.pvRowArray.end(); ++irown ){
		CRow row( multipliersB.Row(), 0 );
		size_t index( 0 );
		for( CRowArray::iterator icolumn( multipliersB.pvRowArray.begin() );
				icolumn != multipliersB.pvRowArray.end(); ++icolumn ){
			row[ index ] = std::inner_product( icolumn->begin(), icolumn->end(),
					irown->begin(), row[ index ] );
			++index;
			}
		result.pvRowArray.push_back( row );
		}
	return result;
}
//*****************************************************************************
int main( int ac, char* av[] ) {

	CMatrix MatrixA;
	CMatrix MatrixB;
	std::cin >> MatrixA;
	if( !std::cin.good() )
		std::cerr << "Error!! read from file." << std::endl;
	std::cout << MatrixA << std::endl;
	std::cin >> MatrixB;
	if( !std::cin.good() && !std::cin.eof() )
		std::cerr << "Error!! read from file." << std::endl;
	std::cout << MatrixB << std::endl;
	//check result size..!!
	if( MatrixA.Column() != MatrixB.Row() ){
		std::cerr << "Can`t multiply the current matrix." << std::endl;
		return 1;
		}
	CMatrix result( MatrixA * MatrixB );
	std::cout << result << std::endl;
	
	return 0;
}
