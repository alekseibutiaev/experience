// spherical2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cassert>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "spherical_cast.hpp"

std::ostream& operator<<( std::ostream& f_out, const glm::vec3& f_value ) {
  f_out << "vec3 x: " << f_value.x << " y: " << f_value.y << " z: " << f_value.z;
  return f_out;
}

std::ostream& operator<<( std::ostream& f_out, const glm::vec4& f_value ) {
  f_out << "vec4 x: " << f_value.x << " y: " << f_value.y << " z: " << f_value.z << " w: " << f_value.w;
  return f_out;
}

std::ostream& operator<<( std::ostream& f_out, const sphere& f_value ) {
  f_out << "sphere d: " << static_cast< float >( f_value.distance ) <<
    " z: " << static_cast< float >( f_value.zenith ) <<
    " a: " << static_cast< float >( f_value.azimuth );
  return f_out;
}

const glm::detail::tvec3< bool > vec3_true( true, true, true );
const float epsilon = 0.0001f;
const float half_pi = 90.0f;
const float pi = 180.0f;

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

const glm::vec3 data2[] = {
  glm::vec3( -1.0f,  1.0f,  -1.0f ), // A
  glm::vec3(  0.0f,  1.0f,  -1.0f ), // B
  glm::vec3(  1.0f,  1.0f,  -1.0f ), // C
  glm::vec3( -1.0f,  1.0f,  0.0f ), // D
  glm::vec3(  0.0f,  1.0f,  0.0f ), // E
  glm::vec3(  1.0f,  1.0f,  0.0f ), // F
  glm::vec3( -1.0f,  1.0f,  1.0f ), // G
  glm::vec3(  0.0f,  1.0f,  1.0f ), // H
  glm::vec3(  1.0f,  1.0f,  1.0f ), // I
  glm::vec3( -1.0f,  0.0f,  -1.0f ), // J
  glm::vec3(  0.0f,  0.0f,  -1.0f ), // K
  glm::vec3(  1.0f,  0.0f,  -1.0f ), // L
  glm::vec3( -1.0f,  0.0f,  0.0f ), // M
  glm::vec3(  0.0f,  0.0f,  0.0f ), // N
  glm::vec3(  1.0f,  0.0f,  0.0f ), // O
  glm::vec3( -1.0f,  0.0f,  1.0f ), // P
  glm::vec3(  0.0f,  0.0f,  1.0f ), // Q
  glm::vec3(  1.0f, -1.0f,  1.0f ), // R
  glm::vec3( -1.0f, -1.0f,  -1.0f ), // S
  glm::vec3(  0.0f, -1.0f,  -1.0f ), // T
  glm::vec3(  1.0f, -1.0f,  -1.0f ), // U
  glm::vec3( -1.0f, -1.0f,  0.0f ), // V
  glm::vec3(  0.0f, -1.0f,  0.0f ), // W
  glm::vec3(  1.0f, -1.0f,  0.0f ), // X
  glm::vec3( -1.0f, -1.0f,  1.0f ), // Y
  glm::vec3(  0.0f, -1.0f,  1.0f ), // Z
  glm::vec3(  1.0f, -1.0f,  1.0f ), // A1
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

void print( const glm::vec3& f_test, const sphere& f_sphere,
    const glm::vec3& f_result ) {
  std::cout << "test " << f_test << std::endl;
  std::cout << "spherical " << f_sphere << std::endl;
  std::cout << "result " << f_result << std::endl;
}

void print( const sphere& f_test,  const glm::vec3& f_cortesian, const sphere& f_result ) {
  std::cout << "test " << f_test << std::endl;
  std::cout << "cortesian " << f_cortesian << std::endl;
  std::cout << "result " << f_result << std::endl;
  std::cout << std::endl;
}


bool compare( const glm::vec3& f_test, const sphere& f_spherical, const glm::vec3& f_result,
    const compare_property& f_property = compare_property() ) {
  const bool result = glm::detail::tvec3< bool >( true, true, true ) ==
      glm::epsilonEqual( f_test, f_result, f_property.epsilon );
  if( !result || f_property.print )
    print( f_test, f_spherical, f_result );
  return result;
}

bool compare( const sphere& f_test, const glm::vec3& f_cortesian, const sphere& f_result,
    const compare_property& f_property = compare_property() ) {
  bool result = glm::epsilonEqual( f_test.distance, f_result.distance, f_property.epsilon );
  if( 0.0f != f_test.distance ) {
    if( half_pi != std::abs( f_test.zenith ) && half_pi  != std::abs( f_result.zenith ) ) {
      float f_test_azimuth = glm::epsilonEqual( pi, std::abs( f_test.azimuth ), f_property.epsilon ) ? pi : f_test.azimuth;
      float f_result_azimuth = glm::epsilonEqual( pi, std::abs( f_test.azimuth ), f_property.epsilon ) ? pi : f_result.azimuth;
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
    const sphere s = f_convert.to_spherical( f_data[ index ] );
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
    const sphere s = f_convert.to_spherical( f_data[ index ] );
    const glm::vec3 r = f_convert.to_cortesian( s );
    if( !compare( f_data[ index ], s, r, f_property ) )
      result = false;
  }
  return result;
}
#endif


#if defined( WIN32 ) || defined( WIN64 )
int main( int ac, _TCHAR* av[] )
#else
int main( int ac, char* av[] )
#endif
{
  int c = 0;
#if 1
  const glm::mat4 mx = glm::rotate( glm::mat4(), 30.0f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
  const glm::mat4 my = glm::rotate( glm::mat4(), 15.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
  const glm::mat4 mz = glm::rotate( glm::mat4(), 60.0f, glm::vec3( 0.0f, 0.0f, 1.0f ) );
  const glm::mat4 mr = mz * my * mx;
  const glm::vec4 rx = mr * glm::vec4( 1.0f, 0.0f, 0.0f, 0.0f );
  const glm::vec4 ry = mr * glm::vec4( 0.0f, 1.0f, 0.0f, 0.0f );
  const glm::vec4 rz = mr * glm::vec4( 0.0f, 0.0f, 1.0f, 0.0f );
  std::cout << "rx " << rx << std::endl;
  std::cout << "ry " << ry << std::endl;
  std::cout << "rz " << rz << std::endl;
  std::cout << std::endl;
  const glm::mat4 mm = mr * glm::mat4();
  std::cout << "mmx " << mm[ 0 ] << std::endl;
  std::cout << "mmy " << mm[ 1 ] << std::endl;
  std::cout << "mmz " << mm[ 2 ] << std::endl;
  std::cout << std::endl;
  std::cout << "mrx " << mr[ 0 ] << std::endl;
  std::cout << "mry " << mr[ 1 ] << std::endl;
  std::cout << "mrz " << mr[ 2 ] << std::endl;
  std::cout << std::endl;

#endif

#if 0
  {
    spherical_cast cc;
    const glm::vec3 t( 2.0f, -1.0f, 3.0f );
    const sphere s = cc.to_spherical( t );
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
    spherical_cast cc( 15.0f, 20.0f, 25.0f );
    const glm::vec3 t( 1.0f, 0.0f,  0.0f );
    const sphere s = cc.to_spherical( t );
    const glm::vec3 r = cc.to_cortesian( s );
    const bool result = compare( t, s, r );
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const bool result = check( ++c, data2, cc, 0.0004f );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( 30.0f, 0.0f, 0.0f );
    const bool result = check( ++c, data2, cc, 0.0005f );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( 0.0f, 30.0f, 0.0f );
    const bool result = check( ++c, data2, cc, 0.0004f );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( 0.0f, 0.0f, 30.0f );
    const bool result = check( ++c, data2, cc, 0.0004f );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }

  {
    spherical_cast cc;
    const bool result = check( ++c, data1, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc;
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( 0.12f, 0.97f, 0.31f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( 15.0f, 20.0f, 30.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( -76.0f, -47.0f, 120.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( -76.0f, -47.0f, -10.0f );
    const bool result = check( ++c, data0, cc, 0.002f );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    spherical_cast cc( 76.1f, 47.0f, 225.0f );
    const bool result = check( ++c, data0, cc );
    std::cout << "test " << c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    bool result = true;
    for( int scrx = static_cast< int >( -pi ); scrx <= static_cast< int >( pi ); scrx += 10 ) {
      for( int scry = static_cast< int >( -pi ); scry <= static_cast< int >( pi ); scry += 10 ) {
        for( int scrz = static_cast< int >( -pi ); scrz <= static_cast< int >( pi ); scrz += 10 ) {
          spherical_cast cc( static_cast< float >( scrx ), static_cast< float >( scry ), static_cast< float >( scrz ) );
          const bool r0 = check( c, data0, cc, 0.0022f );
          const bool r1 = check( c, data1, cc, 0.0022f );
          const bool r2 = check( c, data2, cc, 0.0022f );
          if( result )
            result = r0 && r1 && r2;
        }
      }
    }
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    bool result = true;
    for( int scrx = static_cast< int >( -pi ); scrx <= static_cast< int >( pi ); scrx += 10 ) {
      for( int scry = static_cast< int >( -pi ); scry <= static_cast< int >( pi ); scry += 10 ) {
        for( int scrz = static_cast< int >( -pi ); scrz <= static_cast< int >( pi ); scrz += 10 ) {
          spherical_cast cc( static_cast< float >( scrx ), static_cast< float >( scry ), static_cast< float >( scrz ) );
          for( int zenith = static_cast< int >( -half_pi ); zenith <= static_cast< int >( half_pi ); ++zenith ) {
            for( int azimuth = static_cast< int >( -pi ); azimuth <= static_cast< int >( pi ); ++azimuth ) {
              sphere test( sphere::distance_data( 1.0f ), sphere::zenith_data( static_cast< float >( zenith ) ),
                sphere::azimuth_data( static_cast< float >( azimuth ) ) );
              const glm::vec3 c = cc.to_cortesian( test );
              sphere r = cc.to_spherical( c );
              if( !compare( test, c, r, 0.0443f ) ) {
                result = false;
                print( test, c, r );
              }
            }
          }
        }
      }
    }
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  {
    bool result = true;
    const int denominator = 100;
    for( int scrx = static_cast< int >( -pi ); scrx <= static_cast< int >( pi ); scrx += 10 ) {
      for( int scry = static_cast< int >( -pi ); scry <= static_cast< int >( pi ); scry += 10 ) {
        for( int scrz = static_cast< int >( -pi ); scrz <= static_cast< int >( pi ); scrz += 10 ) {
          spherical_cast cc( static_cast< float >( scrx ), static_cast< float >( scry ), static_cast< float >( scrz ) );
          for( int x = -denominator; x <= denominator; ++x ) {
            for( int y = -denominator; y <= denominator; ++y ) {
              for( int z = -denominator; z <= denominator; ++z ) {
                const glm::vec3 test( static_cast< float >( x ) / static_cast< float >( denominator ),
                  static_cast< float >( y ) / static_cast< float >( denominator ),
                  static_cast< float >( z ) / static_cast< float >( denominator ) );
                const sphere s = cc.to_spherical( test );
                const glm::vec3 r = cc.to_cortesian( s );
                if( !compare( test, s, r, 0.02f ) ) {
                  result = false;
                  print( test, s, r );
                }
              }
            }
          }
        }
      }
    }
    std::cout << "test " << ++c << " is "<< ( result ? "success " : "failure " ) << std::endl;
  }
  return 0;
}

