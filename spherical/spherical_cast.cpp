#include <cmath>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "spherical_cast.hpp"

#if defined( WIN32 ) || defined( WIN64 )
  inline float copysign( const float& f_a, const float& f_b ) {
    return static_cast< float >( _copysign( f_a, f_b ) );
  }
#endif

namespace {
  inline float check_cos( const float f_cos ) {
    if( spherical_cast::one < std::abs( f_cos ) ) {
      assert( false );
      return copysign( 1.0f, f_cos );
    }
    else
      return f_cos;
  }
}; /* namespace */


  spherical_cast::spherical::spherical() : azimuth( 0.0f ), zenith( 0.0f ), distance( 0.0f ) {}
  spherical_cast::spherical::spherical( const float& f_distance, const float& f_zenith, const float& f_azimuth ) :
    distance( f_distance ), zenith( f_zenith ), azimuth( f_azimuth ) {}

  spherical_cast::spherical_cast( const float& f_eps ) : pv_eps( f_eps )  {
  };

  spherical_cast::spherical_cast( const glm::vec3& f_shift, const float& f_eps ) :
      pv_eps( f_eps ), pv_spherical_center( glm::translate( glm::mat4(), -f_shift ) ),
      pv_main_center( glm::inverse( pv_spherical_center ) ) {
  };

  spherical_cast::spherical_cast( const glm::vec3& f_shift, const float& f_pitch, const float& f_yaw,
    const float& f_roll, const float& f_eps ) : pv_eps( f_eps ),
        pv_spherical_center( glm::translate( glm::rotate( glm::rotate( glm::rotate( glm::mat4(),
        f_pitch, glm::vec3( 1.0f, 0.0f, 0.0f ) ), f_yaw, glm::vec3( 0.0f, 1.0f, 0.0f ) ),
        f_roll, glm::vec3( 0.0f, 0.0f, 1.0f ) ), -f_shift ) ),
        pv_main_center( glm::inverse( pv_spherical_center ) ) {
  };

  glm::vec3 spherical_cast::to_cortesian( const spherical_cast::spherical& f_spherical,
      spherical_cast::relatively f_relative ) const {
    return (this->*f_relative)( pv_cortesian( f_spherical ) );
  };

  spherical_cast::spherical spherical_cast::to_spherical( const glm::vec3& f_cortesian,
      spherical_cast::relatively f_relative ) const {
    return pv_spherical( (this->*f_relative)( f_cortesian ) );
  };

  glm::vec3 spherical_cast::as_is( const glm::vec3& f_point ) const {
    return f_point;
  }

  glm::vec3 spherical_cast::at_spherical( const glm::vec3& f_point ) const {
    const glm::vec4 tmp = pv_spherical_center * glm::vec4( f_point, spherical_cast::one );
    return glm::vec3( tmp.x, tmp.y, tmp.z );
  };

  glm::vec3 spherical_cast::at_main( const glm::vec3& f_point ) const {
    const glm::vec4 tmp = pv_main_center * glm::vec4( f_point, spherical_cast::one );
    return glm::vec3( tmp.x, tmp.y, tmp.z );
  };

  spherical_cast::spherical spherical_cast::pv_spherical( const glm::vec3& f_cortesian ) const {
    spherical_cast::spherical result( glm::length( f_cortesian ), 0.0f, 0.0f );
    if( 0.0f == result.distance )
      return result;
    if( glm::epsilonEqual( 0.0f, f_cortesian.x, pv_eps ) &&
          glm::epsilonEqual( 0.0f, f_cortesian.z, pv_eps ) ) {
      result.zenith = spherical_cast::half_pi;
    }
    else {
      float tmp = glm::dot( glm::vec3( 0.0f, 1.0f, 0.0f ), glm::normalize( f_cortesian ) );
      tmp = check_cos( tmp );
      result.zenith = glm::degrees( glm::acos( tmp ) ) - 90;
      if( spherical_cast::pi != std::abs( result.zenith ) ) {
        const glm::vec3 pr_xz = glm::vec3( f_cortesian.x, 0.0f, f_cortesian.z );
        tmp = glm::dot( glm::vec3( 0.0f, 0.0f, 1.0f ), glm::normalize( pr_xz ) );
        tmp = check_cos( tmp );
        result.azimuth = copysign( glm::degrees( glm::acos( tmp ) ), f_cortesian.x );
      }
    }
    result.zenith = copysign( result.zenith, -f_cortesian.y );
    return result;
  }

  glm::vec3 spherical_cast::pv_cortesian( const spherical_cast::spherical& f_spherical ) const {
    glm::vec4 result( 0.0f, 0.0f, f_spherical.distance, 1.0f );
    if( 0.0f != f_spherical.distance ) {
      const glm::mat4 mx = glm::rotate( glm::mat4(), f_spherical.zenith, glm::vec3( 1.0f, 0.0f, 0.0f ) );
      const glm::mat4 my = glm::rotate( glm::mat4(), f_spherical.azimuth, glm::vec3( 0.0f, 1.0f, 0.0f ) );
      const glm::mat4 mr = my * mx;
      result = mr * result;
    }
    return glm::vec3( result.x, result.y, result.z );
  }

const float spherical_cast::epsilon = 0.0001f;
const float spherical_cast::one = 1.0f;
const float spherical_cast::half_pi = 90.0f;
const float spherical_cast::pi = 180.0f;
