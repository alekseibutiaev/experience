// solar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// info
// 3D space аxis
//         ^ z       ^y
//         |        /
//         |       /
//         |      /
//         |     /
//         |    /
//         |   /
//         |  /
//         | /
//         |/
//         *--------->x

#define DEBUG_INPUT 1

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <ctime>

#include <utility>
#include <iomanip>
#include <optional>
#include <iostream>
#include <stdexcept>

#if DEBUG_INPUT
  #include <sstream>
#endif

namespace glm {

  std::ostream&  operator<<(std::ostream& os, const glm::vec3& v) {
    os << "vec3( x: " << v.x << ", y: " << v.y << ", z: " << v.z << " )";
    return os;
  }

} /* namespace glm */

namespace {

  using try_vec3_t = std::optional<glm::vec3>;

  const glm::vec3 ax(1.0f, 0.0f, 0.0f);
  const glm::vec3 ay(0.0f, 1.0f, 0.0f);
  const glm::vec3 az(0.0f, 0.0f, 1.0f);
  const glm::vec3 zero(0.0f, 0.0f, 0.0f);

  struct idata_t {
    float op;                // orbital position
    float rpp;               // rotation period position
    float latitude;          // latitude
    float longitude;         // longitude
    float at;                // axial tilt
  };

  std::ostream&  operator<<(std::ostream& os, const idata_t& v) {
    os << "idata_t( orbital positionx: " << v.op << ", rotation period position: " << v.rpp <<
      ", latitude: " << v.latitude << ", longitude: " << v.longitude << ", axial tilt: " << v.at << " )";
    return os;
  }

  float get_orbital_position(std::tm val) {
    std::tm tmp = { 0 };
    tmp.tm_year = val.tm_year;
    tmp.tm_mday = 1;
    const std::time_t ys = std::mktime(&tmp);
    ++tmp.tm_year;
    const float degrees = 360.0f * (std::mktime(&val) - ys) / (std::mktime(&tmp) - ys);
    return glm::radians(degrees);
  }

  float get_rotation_position(std::tm val) {
    const std::time_t time = (val.tm_hour * 60 + val.tm_min) * 60 + val.tm_sec;
    const float degrees = 360.0f * time / (24 * 60 * 60);
    return glm::radians(degrees);
  }

#if DEBUG_INPUT
  idata_t get_user_data( const std::string& date, const float& latitude, const float& longitude, const float& at) {
    idata_t res;
    std::tm tm = { 0 };
    std::istringstream iss(date);
    iss >> std::get_time(&tm, "%Y %m %d %T");
    res.op = get_orbital_position(tm);
    res.rpp = get_rotation_position(tm);
    res.latitude = glm::radians(latitude);
    res.longitude = glm::radians(longitude);
    res.at = glm::radians(at);
    return res;
  }
#else
  idata_t get_user_data() {
    std::tm tm = {0};
    idata_t res = {0};
    std::cout << "Please input date in format YYYY mm[01 ... 12] dd[01 ... 31] HH[00 ... 23]:MM[00 ... 59]:SS[00 ... 60] ";
    std::cin >> std::get_time(&tm, "%Y %m %d %T");
    if(std::cin.fail())
      throw std::invalid_argument("wrong input data.");
    res.op = get_orbital_position(tm);
    res.rpp = get_rotation_position(tm);
    std::cout << "please input latitude [-90 ... 90]: ";
    std::cin >> res.latitude;
    if(std::cin.fail() || res.latitude < -90.0f || res.latitude > 90.0f)
      throw std::invalid_argument("wrong input latitude.");
    res.latitude = glm::radians(res.latitude);
    std::cout << "please input longitude [-180 ... 180]: ";
    std::cin >> res.longitude;
    if (std::cin.fail() || res.longitude < -180.0f || res.longitude > 180.0f)
      throw std::invalid_argument("wrong input longitude.");
    res.longitude = glm::radians(res.longitude);
    std::cout << "please input  axial tilt [-90 ... 90] positive new year from samer other wise from winter: ";
    std::cin >> res.at;
    if (std::cin.fail() || res.at < -90.0f || res.at > 90.0f)
      throw std::invalid_argument("wrong input axial tilt.");
    res.at = glm::radians(res.at);
    return res;
  }
#endif

  std::pair<glm::vec4, glm::mat4> get_light_direction(const idata_t& v) {
    // https://en.wikipedia.org/wiki/Rotation_matrix
    // creating rotate  matrix around axis Z. for calculate sunlight direction.
    std::pair<glm::vec4, glm::mat4> res;
    res.second = glm::rotate(glm::mat4(1.0f), v.op, az);
    // https://en.wikipedia.org/wiki/Unit_vector
    // rotate unit vector by axis X arount axis X.
    res.first = res.second * glm::vec4(ax, 0.0f);
    return res;
  }

  glm::vec4 get_planet_point(const idata_t& v, const glm::mat4& mtx) {
    // crate two unit vector first by axis X (vwctor for greenwich / prime meridian ),
    // second auxiliary vector by axis Y and rotate both on light direction angle.
    enum { e_greenwich, e_auxiliary, e_count };
    glm::vec4 ar[e_count] = { mtx * glm::vec4(ax, 0.0f), mtx * glm::vec4(ay, 0.0f) };
    // crate rotate matrix atound axis Z on longitude angle plus rotation period.
    const auto lon = glm::rotate(glm::mat4(1.0f), v.longitude + v.rpp, az);
    // rotate both vector on longitude plus rotation period angle.
    for (auto& it : ar)
      it = lon * it;
    // create rotare matrix arount axis auxiliary on latitude angle;
    const auto lat = glm::rotate(glm::mat4(1.0f), v.latitude,
      { ar[e_auxiliary].x, ar[e_auxiliary].y, ar[e_auxiliary].z });
    // get planet points depens of longitude plus rotation period and latitude.
    const auto pp = lat * ar[e_greenwich];
    // create rotate matrix around axis Y on axial tilt angle.
    const auto at = glm::rotate(glm::mat4(1.0f), v.at, ay);
    // rotate planet point for axial tilt angle and return;
    const auto res = at * pp;
    return res;
  }

  // if sunlight is not reachable for planet point then return empty object.
  try_vec3_t get_solar_panel_normal(const glm::vec3& ld, const glm::vec3& pp) {
    // https://en.wikipedia.org/wiki/Normal_(geometry)
    if (0.0f <= glm::dot(ld, pp))
      return try_vec3_t();
    // caltulate vector to sun direction from light direction vector
    const auto tosun = zero - ld;
    // caltulate normale for solar panele and normalize it
    const auto res = glm::normalize(tosun + pp);
    return try_vec3_t(res);
  }

} /* namespace */

int main( int ac, char* av[] ) {
  try {
    // request data from user
#if DEBUG_INPUT
    const idata_t id = get_user_data("2020 01 01 18:00:00", -85.0f, 0.0f, -23.3f);
#else
    const idata_t id = get_user_data();
#endif
    std::cout << id << std::endl;
    // get sun light direction and rotate matrix
    const auto ld = get_light_direction(id);
    std::cout << ld.first << std::endl;
    // get planet ponint depends of longitude, latitude, axial tilt, date & time.
    const auto pp = get_planet_point(id, ld.second);
    // calculate hormal for solat panel 
    if (const auto spn = get_solar_panel_normal(ld.first, pp))
      std::cout << "solar panel normale is " << *spn << std::endl;
    else
      std::cout << "a planet point on the shadow side." << std::endl;
    return 0;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 1;
}
