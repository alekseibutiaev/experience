// capsule.cpp : Defines the entry point for the console application.
//
#if defined( WIN32 ) || defined( WIN64 )
#include "stdafx.h"
#endif

#include <iostream>

#include <glm/glm.hpp>

const glm::vec3 a( 3.0f, 5.0f, 0.0f );
const glm::vec3 b( 10.0f, 9.0f, 0.0f );
const glm::vec3 c0( 2.0f, 2.0f, 0.0f );
const glm::vec3 c1( 5.0f, 9.0f, 0.0f );
const glm::vec3 c2( 13.0f, 8.0f, 0.0f );

bool check_cylinder( const glm::vec3& f_a, const glm::vec3& f_b,
    const float& f_radius, const glm::vec3& f_point ) {
  const glm::vec3 direction = f_a - f_b;
  const glm::vec3 tmp = f_point - f_b;
  if( 0.0f <= glm::dot( direction, tmp ) && 0.0f <= glm::dot( -direction, f_point - f_a ) ) {
    return f_radius >= glm::length( glm::cross( direction, tmp ) ) / glm::length( direction );
}
  return false;
}

bool check_capsule( const glm::vec3& f_a, const glm::vec3& f_b,
    const float& f_radius, const glm::vec3& f_point ) {
  if( check_cylinder( f_a, f_b, f_radius, f_point ) )
    return true;
  return f_radius >= glm::length( f_a - f_point ) || f_radius >= glm::length( f_b - f_point );
}

#if defined( WIN32 ) || defined( WIN64 )
int _tmain( int ac, _TCHAR* av[] ) {
#else
int main( int ac, char* av[] ) {
#endif
  std::cout << ( check_capsule( a, b, 1.0f, c0 ) ? "colide" : "no colide" ) << std::endl;
  std::cout << ( check_capsule( a, b, 4.0f, c0 ) ? "colide" : "no colide" ) << std::endl;
  std::cout << ( check_capsule( a, b, 1.0f, c1 ) ? "colide" : "no colide" ) << std::endl;
  std::cout << ( check_capsule( a, b, 3.0f, c1 ) ? "colide" : "no colide" ) << std::endl;
  std::cout << ( check_capsule( a, b, 1.0f, c2 ) ? "colide" : "no colide" ) << std::endl;
  std::cout << ( check_capsule( a, b, 4.0f, c2 ) ? "colide" : "no colide" ) << std::endl;
	return 0;
}

