//******************************************************************************
//******************************************************************************

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>

//******************************************************************************
template< typename Type, unsigned int LENGHT >
class CLine{
  Type pvLine [LENGHT];
public:
  CLine() {
    std::fill( pvLine, pvLine + LENGHT, Type() );
  }
  unsigned int const Lenght() const {
    return LENGHT;
  }
  Type const& operator[]( unsigned int f_Index ) const {
    if( f_Index >= LENGHT  )
      throw( std::out_of_range( "Index is big!" ) );
    return pvLine[ f_Index ];
  }
  Type& operator[]( unsigned int f_Index ) {
    if( f_Index >= LENGHT  )
      throw( std::out_of_range( "Index is big!" ) );
    return pvLine[ f_Index ];
  }
  void Print() const {
    std::copy( pvLine, pvLine + LENGHT,
	       std::ostream_iterator< Type >( std::cout, " ") );
    std::cout << std::endl;
  }
};
//******************************************************************************
template< typename Type, unsigned int WIDTH, unsigned int HEIGHT >
class CMatrix {
  CLine< Type, WIDTH > pvLines[ HEIGHT ];
public:
//  typedef Type
  unsigned int const Width() const {
    return pvLines->Lenght();
  } 
  unsigned int const Height() const {
    return HEIGHT;
  } 
  CLine< Type, WIDTH > const& operator[]( unsigned int f_Index ) const {
    if( f_Index >= HEIGHT )
      throw( std::out_of_range( "Index is big!" ) );
    return pvLines[ f_Index ];    
  }
  CLine< Type, WIDTH >& operator[]( unsigned int f_Index ) {
    if( f_Index >= HEIGHT )
      throw( std::out_of_range( "Index is big!" ) );
    return pvLines[ f_Index ];
  }
  void Print() const {
    std::for_each( pvLines, pvLines + HEIGHT,
		   std::mem_fun_ref( &CLine< Type, WIDTH >::Print ) );
    std::cout << std::endl;
  }
}; 

//******************************************************************************
template < typename Type, unsigned int COMMON,
	   unsigned int HEIGHT_A, unsigned int WIDTH_B >
CMatrix< Type, WIDTH_B, HEIGHT_A > operator*(
    CMatrix< Type, COMMON, HEIGHT_A >const& f_MatrixA,
    CMatrix< Type, WIDTH_B, COMMON >const& f_MatrixB ){

  CMatrix< Type, WIDTH_B, HEIGHT_A > result;

  for( unsigned int row = 0; row < HEIGHT_A; ++row )
    for( unsigned int col = 0; col < WIDTH_B; ++col )
      for( unsigned int i = 0; i < COMMON; ++i )
	result[col][row] += f_MatrixA[ col ][ i ] * f_MatrixB[ i ][ row ];

  return result;
}
//******************************************************************************

template class CMatrix< int, 10, 10 >;
template class CMatrix< int, 2, 3 >;
template class CMatrix< int, 5, 4 >;

//******************************************************************************

int main( int ac, char* av[] ){
  
  CMatrix< int, 2, 2 > a;
  CMatrix< int, 2, 2 > b;

  a[0][0] = 2;
  a[0][1] = 3;
  a[1][0] = 5;
  a[1][1] = 7;

  b[0][0] = -1;
  b[0][1] = 2;
  b[1][0] = -2;
  b[1][1] = 3;

  a.Print();
  b.Print();
  ( a * b ).Print();  

  return EXIT_SUCCESS;
}


