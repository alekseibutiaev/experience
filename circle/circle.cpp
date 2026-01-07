// circle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cmath>
#include <iostream>
#include <limits>


#if defined( won32 ) || defined( WIN32 )
float copysign( float f_a, float f_b ) {
  return _copysign( f_a, f_b );
}
#endif

template < typename scalar >
class angle {
public:
  static const scalar epsilon;
public:

  angle( const scalar& f_angle = 0.0f ) : pv_angle( f_angle ) {
  }

  angle operator-() const {
    return angle( -pv_angle );
  }

  angle& operator++() {
    pv_angle = pv_correct( pv_angle + 1 );
    return *this;
  }

  angle& operator--() {
    pv_angle = pv_correct( pv_angle - 1 );
    return *this;
  }

  angle operator++()(int) {
    angle result = *this;
    ++(*this);
    return result;
  }

  angle operator--()(int) {
    angle result = *this;
    --(*this);
    return result;
  }

  operator scalar() const {
    return pv_angle;
  }

private:
  float pv_correct( float f_data ) {
    static const scalar half = static_cast< float >( 180.0 );
    static const scalar full = static_cast< float >( 360.0 );
    return std::abs( f_data ) > angle::half ? copysign( angle::full, -f_data ) + f_data : f_data;
  }
private:
  scalar pv_angle;
};

template < typename scalar >
const scalar angle< scalar >::epsilon = std::limits< scalar >::epsilon();

typedef angle< float > anglef;

#if defined( WIN32 ) || defined( WIN64 )
int _tmain(int ac, _TCHAR* av[] )
#else
int main( int ac, char* av[] )
#endif
{
  anglef a = 179.5;
  for( int i = 0; i < 360; ++i ) {
    ++a;
    std::cout << a << std::endl;
  }
  return 0;
}

