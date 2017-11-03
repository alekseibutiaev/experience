// va_list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstdarg>

void pr( const int count, std::va_list f_list ) {
  for( int a = 0; a < 10; ++a ) {
    int m = va_arg( f_list, int );
    std::cout << m << std::endl;
  }
}

#if defined( WIN32 ) || defined( WIN64 )
int _tmain( int ac, _TCHAR* av[] )
#else
int main( int ac, char* av[] )
#endif
{
  int value[ 10 ];
  for( int a = 0; a < 10; ++a )
    value[ a ] = a * 10;
  pr( 10, reinterpret_cast< std::va_list >( value ) );
	return 0;
}

