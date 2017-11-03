#pragma once

#ifndef __SPHERICAL_CAST_HPP__
#define __SPHERICAL_CAST_HPP__

#include <glm/glm.hpp>

class sphere {
public:
  enum sphere_data {
    e_distance, e_zenith, e_azimuth
  };

  template < sphere::sphere_data D >
  class data {
  public:
    inline explicit data( const float& f_value = 0 ) : pv_value( f_value ) {
    }
    inline operator float() const {
      return pv_value;
    }
  private:
    float pv_value;
  };

  typedef sphere::data< sphere::e_distance > distance_data;
  typedef sphere::data< sphere::e_zenith > zenith_data;
  typedef sphere::data< sphere::e_azimuth > azimuth_data;

public:
  sphere() {
  }
  sphere( const sphere::distance_data& f_distance, const sphere::zenith_data& f_zenith,
    const sphere::azimuth_data& f_azimuth ) : distance( f_distance ), zenith( f_zenith ), azimuth( f_azimuth ) {
  }
public:
  sphere::distance_data distance;
  sphere::zenith_data zenith;
  sphere::azimuth_data azimuth;
};

class spherical_cast {
public:
  spherical_cast( const float& f_eps = spherical_cast::eps );
  spherical_cast( const float& f_rotx, const float& f_roty, const float& f_rotz, const float& f_eps = spherical_cast::eps );
  const sphere to_spherical( const glm::vec3& f_point ) const;
  const glm::vec3 to_cortesian( const sphere& f_point ) const;
public:
  static const float eps;
private:
  enum axis { e_x, e_y, e_z, e_auxiliary = e_x, e_zenith = e_y, e_azimuth = e_z };
private:
  const glm::mat4 pv_rotate;
  const float pv_eps;
};

#endif /* __SPHERICAL_CAST_HPP__ */
