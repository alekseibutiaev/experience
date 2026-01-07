//*****************************************************************************
// Name        : sudoku.cpp
// Author      : Butyaev A.Y.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//*****************************************************************************

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <set>

//#define DEBUG

const unsigned int BIGSQUARE = 9;
const unsigned int SMOLSQUARE = 3;
const unsigned int RESOLVED = 1;

template< typename TYPE, unsigned long SIZE >
inline unsigned long array_size( TYPE(&)[ SIZE ] ) {
  return SIZE;
}

template< typename TYPE, unsigned long SIZE >
inline TYPE* array_begin( TYPE(&A)[ SIZE ] ) {
  return &A[ 0 ];
}

template< typename TYPE, unsigned long SIZE >
inline TYPE* array_end( TYPE(&A)[ SIZE ] ) {
  return &A[ SIZE ];
}

template< typename TYPE, unsigned long SIZE >
inline std::pair< TYPE*, TYPE* > array_range( TYPE(&A)[ SIZE ] ) {
  return std::pair< TYPE*, TYPE* >( &A[ 0 ], &A[ SIZE ] );
}

class cell;

typedef std::vector< cell > cels;

inline unsigned int index_for( const unsigned int& f_x, const unsigned int& f_y ) {
  return f_x + BIGSQUARE * f_y;
}

class index_for_this {
public:
  index_for_this( const cell* f_celptr ) : pvcelptr( f_celptr ) {
  }
  bool operator()( const cell& f_cel ) const {
    return pvcelptr == &f_cel;
  }
private:
  const cell* pvcelptr;
};


class cell {
public:
  typedef std::set< unsigned int > cellset;
public:
  cell() : pvset( array_begin( cell::pvinitialize ), array_end( cell::pvinitialize ) ) {
  }
  bool set( cels& f_field, const unsigned int& f_num ) {
    if( RESOLVED == pvset.size() )
      return f_num == *pvset.begin();
    pvset = cellset( &f_num, (&f_num) + 1 );
    return pvupdate( f_field, f_num );
  }
  const cellset& variants() const {
    return pvset;
  }
  bool exclude( cels& f_field, const unsigned int& f_num ) {
    if( 0 < pvset.erase( f_num ) && !unresolved() )
      return pvupdate( f_field, *pvset.begin() );
    return !pvset.empty();
  }
  bool unresolved() const {
    return RESOLVED != pvset.size();
  }
private:
  bool pvupdate( cels& f_field, const unsigned int& f_num ) {
    unsigned int cellindex = std::distance( f_field.begin(), std::find_if(
        f_field.begin(), f_field.end(), index_for_this( this ) ) );
    const unsigned int cellx = cellindex % BIGSQUARE;
    const unsigned int celly = cellindex / BIGSQUARE;
    const unsigned int smolsquarex = cellx / SMOLSQUARE * SMOLSQUARE;
    const unsigned int smolsquarey = celly / SMOLSQUARE * SMOLSQUARE;
    for( unsigned int i = 0; i < BIGSQUARE; ++i )
      if( i != cellx && !f_field[ index_for( i, celly ) ].exclude( f_field, f_num ) )
        return false;
    for( unsigned int i = 0; i < BIGSQUARE; ++i )
      if( i != celly && !f_field[ index_for( cellx, i ) ].exclude( f_field, f_num ) )
        return false;
    for( unsigned int ix = 0; ix < SMOLSQUARE; ++ix )
      for( unsigned int iy = 0; iy < SMOLSQUARE; ++iy ) {
        const unsigned int ax = smolsquarex + ix;
        const unsigned int ay = smolsquarey + iy;
        if( ( cellx != ax || celly != ay ) && !f_field[ index_for( ax, ay
              ) ].exclude( f_field, f_num ) )
          return false;
      }
    return true;
  }
private:
  cellset pvset;
  static const int pvinitialize[ BIGSQUARE ];
};

const int cell::pvinitialize[ BIGSQUARE ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

std::ostream& showcount( std::ostream& f_out, const cels& f_field ) {
  f_out << "****************" << std::endl;
  for( unsigned int y = 0; y < BIGSQUARE; ++y ) {
    f_out << "Line" << y << ": ";
    for( unsigned int x = 0; x < BIGSQUARE; ++x )
      f_out << f_field[ index_for( x, y ) ].variants().size();
    f_out << std::endl;
  }
  return f_out;
}

std::ostream& showresult( std::ostream& f_out, const cels& f_field ) {
  f_out << "****************" << std::endl << "       012345678"<< std::endl;
  for( unsigned int y = 0; y < BIGSQUARE; ++y ) {
    f_out << "Line" << y << ": ";
    for( unsigned int x = 0; x < BIGSQUARE; ++x ) {
      int tmp = f_field[ index_for( x, y ) ].unresolved() ? 0 :
          *f_field[ index_for( x, y ) ].variants().begin();
      f_out << tmp;
    }
    f_out << std::endl;
  }
  return f_out;
}

void solution( const cels& f_field ) {
#ifdef DEBUG
  showcount( std::cout, f_field );
#endif
  // find first unresolved cell
  cels::const_iterator unresolved = std::find_if( f_field.begin(), f_field.end(),
      std::mem_fun_ref( &cell::unresolved ) );
  if( f_field.end() != unresolved ) {
    // get index for unresolved cell;
    unsigned int index = std::distance( f_field.begin(), unresolved );
    // take variants set for unresolved cell.
    const cell::cellset& variants = unresolved->variants();
#ifdef DEBUG
    std::copy( variants.begin(), variants.end(), std::ostream_iterator< int >( std::cout, ", " ) );
    std::cout << "cell index: " << index << std::endl;
#endif
    // check up all variants.
    for( cell::cellset::const_iterator variant = variants.begin();
        variant != variants.end(); ++variant ) {
      cels field = f_field;
#ifdef DEBUG
      std::cout << "Try: " << *variant << " for cell: " << index << std::endl;
#endif
      // try current variant for unresolved cell.
      if( field[ index ].set( field, *variant ) )
        solution( field );
    }
  }
  else
    showresult( std::cout, f_field );
}

struct cellinfo {
  static const unsigned int e_value_count = 3;
  unsigned int x;
  unsigned int y;
  unsigned int v;
};
// choose
unsigned int choose_second( const unsigned int& f_first, const unsigned int& f_second ){
  return f_second;
}

bool load_field( const char* f_filename, cels& f_field ) {
  std::cout << f_filename << std::endl;
  std::ifstream file( f_filename );
  if( file.good() ) {
    std::vector< unsigned int > array;
    std::copy( std::istream_iterator< unsigned int >( file ),
        std::istream_iterator< unsigned int >(), std::back_inserter( array ) );
    if( file.bad() || 0 != array.size() % 3 || array.end() != std::find_if(
        array.begin(), array.end(), std::bind2nd( std::greater< unsigned int >(), 9 ) ) ) {
      std::cerr << "The input file is bad" << std::endl;
      return false;
    }
    for( std::vector< unsigned int >::const_iterator i = array.begin();
        i != array.end(); ) {
      union {
        cellinfo info;
        unsigned int data[ cellinfo::e_value_count ];
      } convert;
      std::transform( array_begin( convert.data ), array_end( convert.data ),
          i, array_begin( convert.data ), choose_second );
      std::advance( i, cellinfo::e_value_count );
      if( !f_field[ index_for( convert.info.x, convert.info.y ) ].set(
            f_field, convert.info.v ) ) {
        std::cerr << "Sudoku error! For X: " << convert.info.x << " Y: " <<
            convert.info.y << " Value: " << convert.info.v << std::endl;
        return false;
      }
    }
    return true;
  }
  return false;
}

int main( int ac, char* av[] ) {
  if( 2 <= ac ) {
    cels field( BIGSQUARE * BIGSQUARE );
    if( !load_field( av[ 1 ], field ) )
      return EXIT_FAILURE;
    solution( field );
  }
  return EXIT_SUCCESS;
}
