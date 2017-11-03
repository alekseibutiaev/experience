// spherical.cpp : Defines the entry point for the console application.
//
#if defined( WIN32 )
#include "stdafx.h"
#endif

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "spherical_cast.hpp"

std::ostream& operator<<( std::ostream& f_ostream, const glm::vec3& f_vec ) {
  f_ostream << "x: " << f_vec.x << " y: " << f_vec.y << " z: " << f_vec.z;
  return f_ostream;
}

std::ostream& operator<<( std::ostream& f_ostream, const spherical_cast::spherical& f_spherical ) {
  f_ostream << "distance: " << f_spherical.distance << " zenith: " << f_spherical.zenith <<
    " azimuth: " << f_spherical.azimuth;
  return f_ostream;
}


const glm::detail::tvec3< bool > vec3_true( true, true, true );
const float epsilon = 0.0001f;

const glm::vec3 data0[] = {

  glm::vec3(  0.0f,   0.0f,  0.0f ),

  glm::vec3(  2.0f,   4.0f,  3.0f ),
  glm::vec3(  2.0f,   4.0f, -3.0f ),
  glm::vec3(  2.0f,  -4.0f,  3.0f ),
  glm::vec3(  2.0f,  -4.0f, -3.0f ),
  glm::vec3( -2.0f,   4.0f,  3.0f ),
  glm::vec3( -2.0f,   4.0f, -3.0f ),
  glm::vec3( -2.0f,  -4.0f,  3.0f ),
  glm::vec3( -2.0f,  -4.0f, -3.0f ),

  glm::vec3(  0.17f,  1.5f,  0.3f ),
  glm::vec3(  0.17f,  1.5f, -0.3f ),
  glm::vec3(  0.17f, -1.5f,  0.3f ),
  glm::vec3(  0.17f, -1.5f, -0.3f ),
  glm::vec3( -0.17f,  1.5f,  0.3f ),
  glm::vec3( -0.17f,  1.5f, -0.3f ),
  glm::vec3( -0.17f, -1.5f,  0.3f ),
  glm::vec3( -0.17f, -1.5f, -0.3f ),

  glm::vec3(  0.17f,  1.5f,  0.0f ),
  glm::vec3(  0.17f,  1.5f,  0.0f ),
  glm::vec3(  0.17f, -1.5f,  0.0f ),
  glm::vec3(  0.17f, -1.5f,  0.0f ),
  glm::vec3( -0.17f,  1.5f,  0.0f ),
  glm::vec3( -0.17f,  1.5f,  0.0f ),
  glm::vec3( -0.17f, -1.5f,  0.0f ),
  glm::vec3( -0.17f, -1.5f,  0.0f ),

  glm::vec3(  0.17f,  0.0f,  0.3f ),
  glm::vec3(  0.17f,  0.0f, -0.3f ),
  glm::vec3(  0.17f,  0.0f,  0.3f ),
  glm::vec3(  0.17f,  0.0f, -0.3f ),
  glm::vec3( -0.17f,  0.0f,  0.3f ),
  glm::vec3( -0.17f,  0.0f, -0.3f ),
  glm::vec3( -0.17f,  0.0f,  0.3f ),
  glm::vec3( -0.17f,  0.0f, -0.3f ),

  glm::vec3(  0.0f,   1.5f,  0.3f ),
  glm::vec3(  0.0f,   1.5f, -0.3f ),
  glm::vec3(  0.0f,  -1.5f,  0.3f ),
  glm::vec3(  0.0f,  -1.5f, -0.3f ),
  glm::vec3(  0.0f,   1.5f,  0.3f ),
  glm::vec3(  0.0f,   1.5f, -0.3f ),
  glm::vec3(  0.0f,  -1.5f,  0.3f ),
  glm::vec3(  0.0f,  -1.5f, -0.3f ),

  glm::vec3(  0.17f,  0.0f,  0.0f ),
  glm::vec3(  0.17f,  0.0f,  0.0f ),
  glm::vec3(  0.17f,  0.0f,  0.0f ),
  glm::vec3(  0.17f,  0.0f,  0.0f ),
  glm::vec3( -0.17f,  0.0f,  0.0f ),
  glm::vec3( -0.17f,  0.0f,  0.0f ),
  glm::vec3( -0.17f,  0.0f,  0.0f ),
  glm::vec3( -0.17f,  0.0f,  0.0f ),

  glm::vec3(  0.0f,   0.0f,  0.3f ),
  glm::vec3(  0.0f,   0.0f, -0.3f ),
  glm::vec3(  0.0f,   0.0f,  0.3f ),
  glm::vec3(  0.0f,   0.0f, -0.3f ),
  glm::vec3(  0.0f,   0.0f,  0.3f ),
  glm::vec3(  0.0f,   0.0f, -0.3f ),
  glm::vec3(  0.0f,   0.0f,  0.3f ),
  glm::vec3(  0.0f,   0.0f, -0.3f ),

  glm::vec3(  0.0f,   1.5f,  0.0f ),
  glm::vec3(  0.0f,   1.5f,  0.0f ),
  glm::vec3(  0.0f,  -1.5f,  0.0f ),
  glm::vec3(  0.0f,  -1.5f,  0.0f ),
  glm::vec3(  0.0f,   1.5f,  0.0f ),
  glm::vec3(  0.0f,   1.5f,  0.0f ),
  glm::vec3(  0.0f,  -1.5f,  0.0f ),
  glm::vec3(  0.0f,  -1.5f,  0.0f ),

};

const glm::vec3 data1[] = {
  glm::vec3(  0.0f,   0.0f,  0.0f ),
  glm::vec3(  0.0f,   0.0f,  1.0f ),
  glm::vec3(  0.0f,   0.0f, -1.0f ),
  glm::vec3(  0.0f,   1.0f,  0.0f ),
  glm::vec3(  0.0f,  -1.0f,  0.0f ),
  glm::vec3(  1.0f,   0.0f,  0.0f ),
  glm::vec3( -1.0f,   0.0f,  0.0f ),
};

struct compare_property {
  compare_property() : print( false ), epsilon( ::epsilon ) {
  }
  compare_property( const bool& f_print ) : print( f_print ), epsilon( ::epsilon ) {
  }
  compare_property( const float& f_epsilon ) : print( false ), epsilon( f_epsilon ) {
  }
  compare_property( const bool& f_print, const float& f_epsilon ) : print( f_print ), epsilon( f_epsilon ) {
  }
  const bool print;
  const float epsilon;
};

void print( const glm::vec3& f_test, const spherical_cast::spherical& f_spherical,
    const glm::vec3& f_result ) {
  std::cout << "test " << f_test << std::endl;
  std::cout << "spherical " << f_spherical << std::endl;
  std::cout << "result " << f_result << std::endl;
}

void print( const spherical_cast::spherical& f_test,  const glm::vec3& f_cortesian,
      const spherical_cast::spherical& f_result ) {
  std::cout << "test " << f_test << std::endl;
  std::cout << "cortesian " << f_cortesian << std::endl;
  std::cout << "result " << f_result << std::endl;
  std::cout << std::endl;
}


bool compare( const glm::vec3& f_test,  const spherical_cast::spherical& f_spherical,
      const glm::vec3& f_result, const compare_property& f_property = compare_property() ) {
  const bool result = glm::detail::tvec3< bool >( true, true, true ) ==
      glm::epsilonEqual( f_test, f_result, f_property.epsilon );
  if( !result || f_property.print )
    print( f_test, f_spherical, f_result );
  return result;
}

bool compare( const spherical_cast::spherical& f_test,  const glm::vec3& f_cortesian,
      const spherical_cast::spherical& f_result, const compare_property& f_property = compare_property() ) {
  bool result = glm::epsilonEqual( f_test.distance, f_result.distance, f_property.epsilon );
  if( 0.0f != f_test.distance ) {
    if( spherical_cast::half_pi != std::abs( f_test.zenith ) && spherical_cast::half_pi != std::abs( f_result.zenith ) ) {
      float f_test_azimuth = glm::epsilonEqual( 180.0f, std::abs( f_test.azimuth ), f_property.epsilon ) ? 180 : f_test.azimuth;
      float f_result_azimuth = glm::epsilonEqual( 180.0f, std::abs( f_test.azimuth ), f_property.epsilon ) ? 180 : f_result.azimuth;
      result = vec3_true == glm::epsilonEqual( glm::vec3( f_test.distance, f_test.zenith, f_test_azimuth ),
          glm::vec3( f_result.distance, f_result.zenith, f_result_azimuth), f_property.epsilon );
    }
  }
  if( !result || f_property.print )
    print( f_test, f_cortesian, f_result );
  return result;
}

template < unsigned int N >
bool check( const int& f_test, const glm::vec3(&f_data)[N], const spherical_cast& f_convert,
      const compare_property& f_property = compare_property() ) {
  bool result = true;
  for( unsigned int index = 0; index < N; ++index ) {
    const spherical_cast::spherical s = f_convert.to_spherical( f_data[ index ] );
    const glm::vec3 r = f_convert.to_cortesian( s );
    if( !compare( f_data[ index ], s, r, f_property ) )
      result = false;
  }
  return result;
}
#if 0
template < unsigned int N >
bool check( const int& f_test, const glm::vec3(&f_data)[N], const spherical_cast& f_convert,
      const compare_property& f_property = compare_property() ) {
  bool result = true;
  for( unsigned int index = 0; index < N; ++index ) {
    const spherical_cast::spherical s = f_convert.to_spherical( f_data[ index ] );
    const glm::vec3 r = f_convert.to_cortesian( s );
    if( !compare( f_data[ index ], s, r, f_property ) )
      result = false;
  }
  return result;
}
#endif
#if defined( _DEBUG ) || defined( DEBUG )
int _tmain( int ac, _TCHAR* av[] ) {
#else
int main( int ac, char* av[] ) {
#endif
  int c = 0;
#if 1
  {
    spherical_cast cc;
    const glm::vec3 t( 2.0f, -1.0f, 3.0f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 stick( 0.0f, 0.0f, s.distance );
    const glm::quat qx = glm::angleAxis( s.zenith, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    const glm::quat qy = glm::angleAxis( s.azimuth, glm::vec3( 0.0f, 1.0f, 0.0f ) );
//    const glm::quat qz = glm::angleAxis( 18.94f, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    const glm::quat qr = qy * qx/* * qz*/;

    const glm::quat stickr = qr * glm::quat( 0, stick ) * glm::conjugate( qr );
    glm::vec3 tmp1( stickr.x, stickr.y, stickr.z );

    std::cout << "tmp1 x:" << tmp1.x << " y: " << tmp1.y << " z: " << tmp1.z << std::endl;
    std::cout << std::endl;


  }
#endif
  {
    spherical_cast cc;
    const glm::vec3 t( 1.0f, 1.0f, 1.0f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r, true );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const glm::vec3 t( 1.0f, -1.0f, 1.0f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const glm::vec3 t( 1.0f, -2.0f, 3.0f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3( 4.0f, 2.0f, 0.0f ), 0.0f, 0.0f, -30.0f );
    const glm::vec3 check( 6.03730f, 6.87128f, 0.0f );
    const glm::vec3 test( 4.2f, 3.2f, 0.0f );
    const glm::vec3 r = cc.at_main( test );
    const bool result = vec3_true == glm::epsilonEqual( check, r, ::epsilon );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const glm::vec3 t( 0.0f, 1.5f, 0.0f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const glm::vec3 t( 0.0f, -1.5f, 0.0f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc = spherical_cast( glm::vec3( -1.5f, 2.3f, 0.7f ) );
    const glm::vec3 t( 3.9f, 4.5f, 5.2f );
    const spherical_cast::spherical s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const bool result = check( ++c, data1, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3( 32.5f, 51.4f, 63.7f ) );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3( -1.5f, 2.3f, 0.7f ), 0.0f, 0.0f, 0.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3(), 15.0f, 20.0f, 30.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3( -1.5f, 2.3f, 3.7f ), 76.0f, 47.0f, 120.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3( -2.1f, 13.3f, 5.7f ), -76.0f, -47.0f, -10.0f );
    const bool result = check( ++c, data0, cc, 0.002f );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( glm::vec3( -4.6f, -31.7f, -64.1f ), -76.0f, -47.0f, -10.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    bool result = true;
    spherical_cast cc( glm::vec3( -4.6f, -3.5f, -4.9f ), 97.1f, -17.3f, -23.4f );
    for( int zenith = static_cast< int >( -spherical_cast::half_pi ); zenith <= static_cast< int >( spherical_cast::half_pi ); ++zenith ) {
      for( int azimuth = static_cast< int >( -spherical_cast::pi ); azimuth <= static_cast< int >( spherical_cast::pi ); ++azimuth ) {
        spherical_cast::spherical test( 1.0f, static_cast< float >( zenith ), static_cast< float >( azimuth ) );
        const glm::vec3 c = cc.to_cortesian( test );
        spherical_cast::spherical r = cc.to_spherical( c );
        if( !compare( test, c, r, 0.02f ) ) {
          result = false;
          print( test, c, r );
        }
      }
    }
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    bool result = true;
    const int denominator = 100;
    spherical_cast cc( glm::vec3( -4.6f, -3.5f, -4.9f ), -35.0f, 47.0f, -50.0f );
    for( int x = -denominator; x <= denominator; ++x ) {
      for( int y = -denominator; y <= denominator; ++y ) {
        for( int z = -denominator; z <= denominator; ++z ) {
          const glm::vec3 test( static_cast< float >( x ) / static_cast< float >( denominator ),
            static_cast< float >( y ) / static_cast< float >( denominator ),
            static_cast< float >( z ) / static_cast< float >( denominator ) );
          const spherical_cast::spherical s = cc.to_spherical( test );
          const glm::vec3 r = cc.to_cortesian( s );
          if( !compare( test, s, r, 0.01f ) ) {
            result = false;
            print( test, s, r );
          }
        }
      }
    }
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
	return 0;
}

