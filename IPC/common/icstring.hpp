//*****************************************************************************
//    Project : pu40
//       File : icstring.hpp
// Created on : Jul 6, 2010
//     Author : butyaev
//       Name : Butyaev A.Y.
//     e-mail : alex-b@liskom.ru
//*****************************************************************************

#ifndef __ICSTRING_HPP__
#define __ICSTRING_HPP__

#include <string>

#include "chartype.h"

namespace common {

  struct ignoring_case_char_traits : public std::char_traits< char > {

    static int compare(const char_type* f_StringA, const char_type* f_StringB,
        size_t f_Lenght) {
      for( size_t index = 0; index < f_Lenght; ++index )
        if( lt( f_StringA[ index ], f_StringB[ index ] ) )
          return -1;
        else if( lt( f_StringB[ index ], f_StringA[ index ] ) )
          return 1;
      return 0;
    }

    static const char_type* find( const char_type* f_String, size_t f_Lenght,
        const char_type& f_Patern ) {
      for( std::size_t index = 0; index < f_Lenght; ++index )
        if( eq( f_String[ index ], f_Patern ) )
          return f_String + index;
      return 0L;
    }

    static bool eq( const char_type& f_CharA, const char_type& f_CharB ) {
      return wtoupper( f_CharA ) == wtoupper( f_CharB );
    }

    static bool lt( const char_type& f_CharA, const char_type& f_CharB ) {
      return wtoupper( f_CharA ) < wtoupper( f_CharB );
    }

  };

  typedef std::basic_string< char, ignoring_case_char_traits,
      std::allocator< char > > icstring;

}; /* namespace common */

#endif /* __ICSTRING_HPP__ */
