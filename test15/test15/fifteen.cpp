#include "stdafx.h"

#include <cstdlib>

#include <algorithm> 
#include <iostream> 

#include "array_help.hpp"

#include "fifteen.hpp"

namespace {


  class check {
  public:
    check() : pv_check( -1 ) {
    }
    bool operator()( const int& f_value ) {
      if( pv_right_distance == f_value - pv_check ) {
        ++pv_check;
        return false;
      }
      return true;
    }
  private:
    int pv_check;
  private:
    static const int pv_right_distance = 1;
  };
}; /* namespace */

fifteen::fifteen() : pv_field( fifteen::max_pieces ) {
//  unsigned int index = 0;
  for( int value = 0; value < fifteen::max_pieces - 1; ++value )
    pv_field[ value ] = value;
  pv_field[ fifteen::max_pieces - 1 ] = fifteen::unused_cell;
  unsigned int to = fifteen::max_pieces - 1;
  for( unsigned int count = 0; count < pv_mix_count; ++count ) {
    std::vector< unsigned int > froms = pv_can_be_selected( to );
    const unsigned int index = static_cast< unsigned int >( rand() % froms.size() );
    const unsigned int from = froms[ index ];
    move( from, to );
    to = from;
  }
  return;
}

int fifteen::select( const unsigned int& f_pos ) {
  if( f_pos <= max_pieces ) {
    pv_selected = f_pos;
    return pv_field[ f_pos ];
  }
  return unused_cell;
}

unsigned int fifteen::can_move( const fifteen::direction& f_direction ) {
  unsigned int result;

  switch( f_direction ) {
    case fifteen::e_left :
      result = pv_selected - 1;
      break;
    case fifteen::e_right :
      result = pv_selected + 1;
      break;
    case fifteen::e_top :
      result = pv_selected - field_height;
      break;
    case fifteen::e_bottom :
      result = pv_selected + field_height;
      break;
  }
  if( 0 <= result && result < max_pieces && unused_cell == pv_field[ result ] )
    return result;
  return max_pieces;
}

void fifteen::move( const unsigned int& f_from, const unsigned int& f_to ) {
  std::swap( pv_field[ f_from ], pv_field[ f_to ] );
}

bool fifteen::ready() const {
  const bool result = pv_field.end() - 1 == std::find_if( pv_field.begin(), pv_field.end() - 1, check() );
  if( result )
    std::cout << std::endl;
  return result;
}

fifteen::const_iterator fifteen::begin() const {
  return pv_field.begin();
}

fifteen::const_iterator fifteen::end() const{
  return pv_field.end();
}

std::vector< unsigned int > fifteen::pv_can_be_selected( const unsigned int& f_to ) {
  static const int shift[] = { 1, -1, static_cast< int >( field_width ),
    -static_cast< int >( field_width ) };
  std::vector< unsigned int > result;
  for( unsigned int index = 0; index < array_size( shift ); ++index ) {
    const int from = f_to + shift[ index ];
    if( 2 > index && f_to / fifteen::field_width != from / fifteen::field_width )
      continue;
    if( 0 <= from && from < max_pieces )
      result.push_back( static_cast< unsigned int >( from ) );
  }
  return result;
}
