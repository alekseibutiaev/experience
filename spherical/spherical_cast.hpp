#pragma once

#ifndef __SPHERICAL_HPP__
#define __SPHERICAL_HPP__

class spherical_cast {
public:
  struct spherical {
    spherical();
    spherical( const float& f_distance, const float& f_zenith, const float& f_azimuth );
    float distance;
    float zenith;
    float azimuth;
  };
  typedef glm::vec3 (spherical_cast::*relatively)( const glm::vec3& ) const;
public:
  spherical_cast( const float& f_eps = spherical_cast::epsilon );
  spherical_cast( const glm::vec3& f_shift, const float& f_eps = spherical_cast::epsilon );
  spherical_cast( const glm::vec3& f_shift, const float& f_pitch, const float& f_yaw,
    const float& f_roll, const float& f_eps = spherical_cast::epsilon );
  glm::vec3 to_cortesian( const spherical_cast::spherical& f_spherical,
      spherical_cast::relatively f_relative = &spherical_cast::at_main ) const;
  spherical_cast::spherical to_spherical( const glm::vec3& f_cortesian,
      spherical_cast::relatively f_relative = &spherical_cast::at_spherical  ) const;
  glm::vec3 as_is( const glm::vec3& f_point ) const;
  glm::vec3 at_spherical( const glm::vec3& f_point ) const;
  glm::vec3 at_main( const glm::vec3& f_point ) const;
public:
  static const float epsilon;
  static const float one;
  static const float half_pi;
  static const float pi;
private:
  spherical_cast::spherical pv_spherical( const glm::vec3& f_cortesian ) const;
  glm::vec3 pv_cortesian( const spherical_cast::spherical& f_spherical ) const;
private:
  const float pv_eps; 
  glm::mat4 pv_spherical_center;
  glm::mat4 pv_main_center;
};

#endif /* __SPHERICAL_HPP__ */
