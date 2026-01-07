#include "stdafx.h"

#include <cmath>
#include <glm/ext.hpp>

#include "spherical_cast.hpp"

#if defined( WIN32 ) || defined( WIN64 )
  inline float copysign( const float& f_a, const float& f_b ) {
    return static_cast< float >( _copysign( f_a, f_b ) );
  }
#endif

namespace {

  inline float correct_cos( const float f_cos ) {
    static const float max_cos = 1.0f;
    return max_cos < std::abs( f_cos ) ? copysign( max_cos, f_cos ) : f_cos;
  }

  inline glm::vec3 vec3( const glm::vec4& f_vec ) {
    return glm::vec3( f_vec.x, f_vec.y, f_vec.z );
  }

}; /* namespace */

const float spherical_cast::eps = 0.0001f;

spherical_cast::spherical_cast( const float& f_eps ) : pv_eps( f_eps ) {
}

spherical_cast::spherical_cast( const float& f_rotx, const float& f_roty, const float& f_rotz, const float& f_eps ) :
    pv_rotate( glm::rotate( glm::rotate( glm::rotate( glm::mat4(), f_rotx, glm::vec3( 1.0f, 0.0f, 0.0f ) ), f_roty,
    glm::vec3( 0.0f, 1.0f, 0.0f ) ), f_rotz, glm::vec3( 0.0f, 0.0f, 1.0f ) ) ), pv_eps( f_eps ) {
}

const sphere spherical_cast::to_spherical( const glm::vec3& f_point ) const {
  sphere result( sphere::distance_data( glm::length( f_point ) ), sphere::zenith_data(),
    sphere::azimuth_data() );
  if( 0.0f == result.distance )
    return result;
  const glm::vec4 npoint = glm::vec4( f_point / static_cast< float >( result.distance ), 0.0f );
  const glm::vec4& zenith = pv_rotate[ spherical_cast::e_zenith ];
  float cos = glm::dot( zenith, npoint );
  cos = correct_cos( cos );
  result.zenith = sphere::zenith_data( glm::degrees( glm::acos( cos ) ) - 90.0f );
  if( 1.0f != std::abs( cos ) ) {
    const glm::vec4 prj = glm::normalize( npoint - zenith * cos );
    cos = glm::dot( pv_rotate[ spherical_cast::e_azimuth ], prj );
    cos = correct_cos( cos );
    const float sign = glm::dot( pv_rotate[ spherical_cast::e_auxiliary ], prj );
    result.azimuth = sphere::azimuth_data( copysign( glm::degrees( glm::acos( cos ) ), sign ) );
  }
  return result;
}

const glm::vec3 spherical_cast::to_cortesian( const sphere& f_point ) const {
  if( 0.0f != f_point.distance ) {
#if 0
    const glm::mat4 my = glm::rotate( glm::mat4(), static_cast< float >( f_point.azimuth ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
    const glm::mat4 mx = glm::rotate( glm::mat4(), static_cast< float >( f_point.zenith ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
    const glm::mat4 mr = pv_rotate * my * mx;
    return vec3( mr * glm::vec4( 0.0f, 0.0f, f_point.distance, 0.0f ) );
#elif 0
    const glm::mat4 mr = glm::rotate( glm::rotate( pv_rotate, static_cast< float >( f_point.azimuth ),
      glm::vec3( 0.0f, 1.0f, 0.0f ) ), static_cast< float >( f_point.zenith ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
    return vec3( mr * glm::vec4( 0.0f, 0.0f, f_point.distance, 0.0f ) );
#else
    const glm::mat4 my = glm::rotate( glm::mat4(), static_cast< float >( f_point.azimuth ), vec3( pv_rotate[ spherical_cast::e_y ] ) );
    const glm::mat4 mx = glm::rotate( glm::mat4(), static_cast< float >( f_point.zenith ), vec3( pv_rotate[ spherical_cast::e_x ] ) );
    const glm::mat4 mr = my * mx;
    return vec3( mr * ( pv_rotate[ spherical_cast::e_z ] * static_cast< float >( f_point.distance ) ) );
#endif
  }
  return glm::vec3();
}
