//============================================================================
// Name        : convertor.cpp
// Author      : Butyaev Alexey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#if defined( WIN32 )
#include "stdafx.h"
#endif

#include <math.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#if defined( WIN32 )
float copysign( float f_a, float f_b ) {
  return static_cast< float >( _copysign( f_a, f_b ) );
}
#endif

struct spherical {
  float azimuth;
  float zenith;
  float distance;
};

#if 0
spherical coordinate_cast( const glm::vec3& f_point, const glm::vec3& f_shift,
      const glm::mat4& f_orientation ) {
  spherical result = { 0.0f, 0.0f, 0.0f };
  const glm::vec4 tr = glm::vec4( f_point - f_shift, 1.0f ) * f_orientation;
  const glm::vec3 tmp = glm::vec3( tr.x, tr.y, tr.z );
  if( 0.0f != ( result.distance = glm::length( tmp ) ) ) {
    result.azimuth = copysign( glm::angle( glm::normalize( glm::vec2( tmp.z, tmp.y ) ), unit ), tmp.y );
    result.zenith = copysign( glm::angle( glm::normalize( glm::vec2( tmp.z, tmp.x ) ), unit ), tmp.x );
  }
  return result;
}

glm::vec3 coordinate_cast( const spherical& f_point, const glm::vec3& f_shift,
     const glm::mat4& f_orientation ) {
  glm::vec3 tmp;
  if( 0.0f != f_point.distance  ) {
    const glm::vec2 rx = glm::rotate( unit, f_point.zenith );
    const glm::vec2 ry = glm::rotate( unit, f_point.azimuth );
    tmp = glm::vec3( copysign( ry.x * rx.y, f_point.zenith ),
      copysign( rx.x * ry.y, f_point.azimuth ), copysign( rx.x * ry.x, rx.x ) );
    const glm::vec4 result = glm::vec4( glm::normalize( tmp ) * f_point.distance, 1.0f ) * f_orientation;
    tmp = glm::vec3( result.x, result.y, result.z );
  }
  return tmp + f_shift;
}
#else
const glm::vec2 unit( 1.0f, 0.0f );
spherical coordinate_cast( const glm::vec3& f_point, const glm::vec3& f_shift,
      const glm::mat4& f_orientation ) {
  spherical result = { 0.0f, 0.0f, 0.0f };
  const glm::vec4 tr = glm::vec4( f_point - f_shift, 1.0f ) * f_orientation;
  const glm::vec3 tmp = glm::vec3( tr.x, tr.y, tr.z );
  if( 0.0f != ( result.distance = glm::length( tmp ) ) ) {
    result.azimuth = copysign( glm::angle( glm::normalize( glm::vec2( tmp.z, tmp.x ) ), unit ), tmp.x );
    result.zenith = -copysign( glm::angle( glm::normalize( glm::vec2( tmp.z, tmp.y ) ), unit ), tmp.y );
  }
  return result;
}

glm::vec3 coordinate_cast( const spherical& f_point, const glm::vec3& f_shift,
     const glm::mat4& f_orientation ) {
  glm::vec3 tmp;
  if( 0.0f != f_point.distance  ) {
    const glm::vec2 rx = glm::rotate( unit, f_point.zenith );
    const glm::vec2 ry = glm::rotate( unit, f_point.azimuth );
    tmp = glm::vec3( copysign( rx.x * ry.y, f_point.azimuth ),
      copysign( ry.x * rx.y, -f_point.zenith ), copysign( rx.x * ry.x, rx.x ) );
    const glm::vec4 result = glm::vec4( glm::normalize( tmp ) * f_point.distance, 1.0f ) * f_orientation;
    tmp = glm::vec3( result.x, result.y, result.z );
  }
  return tmp + f_shift;
}
#endif
const glm::vec3 sign1[] = {
    glm::vec3(  1.0f,  1.0f,  1.0f ),
    glm::vec3(  1.0f,  1.0f, -1.0f ),
    glm::vec3(  1.0f, -1.0f,  1.0f ),
    glm::vec3(  1.0f, -1.0f, -1.0f ),
    glm::vec3( -1.0f,  1.0f,  1.0f ),
    glm::vec3( -1.0f,  1.0f, -1.0f ),
    glm::vec3( -1.0f, -1.0f,  1.0f ),
    glm::vec3( -1.0f, -1.0f, -1.0f ),
};

const glm::vec3 sign2[] = {
    glm::vec3(  2.0f,  3.0f,  1.0f ),
    glm::vec3(  2.0f,  3.0f, -1.0f ),
    glm::vec3(  2.0f, -3.0f,  1.0f ),
    glm::vec3(  2.0f, -3.0f, -1.0f ),
    glm::vec3( -2.0f,  3.0f,  1.0f ),
    glm::vec3( -2.0f,  3.0f, -1.0f ),
    glm::vec3( -2.0f, -3.0f,  1.0f ),
    glm::vec3( -2.0f, -3.0f, -1.0f ),
    glm::vec3(  0.175f,  1.5f,  0.3f ),
    glm::vec3(  0.175f,  1.5f, -0.3f ),
    glm::vec3(  0.175f, -1.5f,  0.3f ),
    glm::vec3(  0.175f, -1.5f, -0.3f ),
    glm::vec3( -0.175f,  1.5f,  0.3f ),
    glm::vec3( -0.175f,  1.5f, -0.3f ),
    glm::vec3( -0.175f, -1.5f,  0.3f ),
    glm::vec3( -0.175f, -1.5f, -0.3f ),
};

template < unsigned int N >
bool check( const glm::vec3(&f_data)[ N ], const float& f_pitch, const float& f_yaw,
    const float& f_roll, const glm::vec3& f_shift, const int& f_testnum, const float& f_epsilon = 0.001f ) {
if( 6 == f_testnum )
  std::cout << std::endl;
  std::cout << std::endl << "test " << f_testnum << std::endl << std::endl;
  const glm::detail::tvec3< bool > vec3true( true, true, true );
  const glm::mat4 pitch = glm::rotate( glm::mat4(), f_pitch, glm::vec3( 1.0f, 0.0f, 0.0f ) );
  const glm::mat4 yaw = glm::rotate( glm::mat4(), f_yaw, glm::vec3( 0.0f, 1.0f, 0.0f ) );
  const glm::mat4 roll = glm::rotate( glm::mat4(), f_roll, glm::vec3( 0.0f, 0.0f, 1.0f ) );
  const glm::mat4 to = pitch * yaw * roll;
  const glm::mat4 from = glm::transpose( roll ) * glm::transpose( yaw ) * glm::transpose( pitch );
  for( unsigned int i = 0; i < N; ++i ) {
    const spherical s = coordinate_cast( f_data[ i ], f_shift, to );
    const glm::vec3 r = coordinate_cast( s, f_shift, from );
    std::cout << "test   x: " << f_data[ i ].x  << ", y: " << f_data[ i ].y  << ", z: " << f_data[ i ].z << std::endl;
    std::cout << "spherical az: " << s.azimuth << ", zh: " << s.zenith << ", l: " << s.distance << std::endl;
    std::cout << "result x: " << r.x  << ", y: " << r.y  << ", z: " << r.z << std::endl << std::endl;
    if( vec3true != glm::epsilonEqual( f_data[ i ], r, f_epsilon  ) )
      return false;
  }
  return true;
}

#if defined( WIN32 )
int _tmain() {
#else
int main() {
#endif
  std::cout << __FUNCTION__ << std::endl;
{
  const glm::vec4 a( 1.0f, 1.0f, 1.0f, 1.0f );
  const glm::mat4 tr = glm::translate( glm::mat4( 1.0f ), glm::vec3( 5.0f, 3.0f, 1.0f ) );
  const glm::vec4 r = tr * a;
  std::cout << r.x << " " << r.y << " " << r.z << " " << std::endl;
}
{
  const glm::vec2 m( 3.0f, 1.0f );
  const glm::vec2 s( -2.0f, -3.0f );
  const glm::vec2 r = m - s;
  std::cout << r.x << " " << r.y << std::endl;
}
{
  const glm::vec3 m( -2.0f, 2.0f, 6.0f );
  const glm::vec3 s( -11.0f, 5.0f, 6.0f );
  const glm::vec3 r = m - s;
  std::cout << r.x << " " << r.y << " " << r.z << std::endl;
}
  int testn = 0;

  {
    std::cout << std::endl << "test " << ++testn << std::endl << std::endl;
    const glm::vec3 shift = glm::vec3( 0.0f, 0.0f, 0.0f );
    const glm::vec3 test( 4.0f, 3.0f, 2.0f );
    const spherical s = coordinate_cast( test, shift, glm::mat4() );
    glm::vec3 r = coordinate_cast( s, shift, glm::mat4() );
    std::cout << "test x: " << test.x  << ", y: " << test.y  << ", z: " << test.z << std::endl;
    std::cout << "spherical az: " << s.azimuth << ", zh: " << s.zenith << ", l: " << s.distance << std::endl;
    std::cout << "result x: " << r.x  << ", y: " << r.y  << ", z: " << r.z << std::endl;
  }
  {
    std::cout << std::endl << "test " << ++testn << std::endl << std::endl;
    const glm::vec3 shift = glm::vec3( 0.0f, 0.0f, 0.0f );
    const glm::vec3 test( 4.0f, 3.0f, 2.0f );
    const spherical s = coordinate_cast( test, shift, glm::mat4() );
    glm::vec3 r = coordinate_cast( s, shift, glm::mat4() );
    std::cout << "test x: " << test.x  << ", y: " << test.y  << ", z: " << test.z << std::endl;
    std::cout << "spherical az: " << s.azimuth << ", zh: " << s.zenith << ", l: " << s.distance << std::endl;
    std::cout << "result x: " << r.x  << ", y: " << r.y  << ", z: " << r.z << std::endl;
  }
  {
    std::cout << std::endl << "test " << ++testn << std::endl << std::endl;
    const glm::vec3 shift = glm::vec3( 0.0f, 0.0f, 0.0f );
    const glm::vec3 test( 3.0f, 3.0f, 3.0f );
    const spherical s = coordinate_cast( test, shift, glm::mat4() );
    glm::vec3 r = coordinate_cast( s, shift, glm::mat4() );
    std::cout << "test x: " << test.x  << ", y: " << test.y  << ", z: " << test.z << std::endl;
    std::cout << "spherical az: " << s.azimuth << ", zh: " << s.zenith << ", l: " << s.distance << std::endl;
    std::cout << "result x: " << r.x  << ", y: " << r.y  << ", z: " << r.z << std::endl;
  }
  {
    std::cout << std::endl << "test " << ++testn << std::endl << std::endl;
    const glm::vec3 shift = glm::vec3( 2.4f, -6.5, 3.9f );
    const glm::mat4 rotx = glm::rotate( glm::mat4(), 17.3f, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    const glm::mat4 roty = glm::rotate( glm::mat4(), 37.5f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    const glm::mat4 rotz = glm::rotate( glm::mat4(), 43.1f, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    const glm::mat4 tr = rotx * roty * rotz;
    const glm::mat4 tr1 = glm::transpose( rotz ) * glm::transpose( roty ) * glm::transpose( rotx );
    const glm::vec3 test( 2.0f, 3.0f, 1.0f );
    const spherical s = coordinate_cast( test, shift, tr );
    glm::vec3 r = coordinate_cast( s, shift, tr1 );
    std::cout << "test x: " << test.x  << ", y: " << test.y  << ", z: " << test.z << std::endl;
    std::cout << "spherical az: " << s.azimuth << ", zh: " << s.zenith << ", l: " << s.distance << std::endl;
    std::cout << "result x: " << r.x  << ", y: " << r.y  << ", z: " << r.z << std::endl;
  }
  if( !check( sign1, 0.0f, 0.0f, 0.0f, glm::vec3( 0.0f, 0.0f, 0.0f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  if( !check( sign1, 0.0f, 0.0f, 0.0f, glm::vec3( 1.5f, 1.5f, 1.5f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  if( !check( sign1, 10.0f, 80.0f, 50.0f, glm::vec3( 1.0f, 1.0f, 1.0f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  if( !check( sign1, 15.3f, 0.0f, 0.0f, glm::vec3( 0.0f, 0.0f, 0.0f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  if( !check( sign2, 0.0f, 63.7f, 0.0f, glm::vec3( 51.2f, 32.1f, -6.5f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  if( !check( sign2, 0.0f, 0.0f, -41.0f, glm::vec3( 2.7f, -4.1f, 3.8f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  if( !check( sign2, 10.43f, 15.1f, 31.5f, glm::vec3( 0.12f, -1.1f, 1.15f ), ++testn ) )
    std::cerr << "test " << testn << " failure" << std::endl;
  std::cout << std::endl;
  return 0;
}

