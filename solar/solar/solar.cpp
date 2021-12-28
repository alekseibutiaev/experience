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
//         ^ z   ^y
//         |    /
//         |   /
//         |  /
//         | /
//         |/
//         *---->x

#define DEBUG_INPUT 1

#include <ctime>

#include <utility>
#include <iomanip>
#include <optional>
#include <iostream>
#include <stdexcept>

#if DEBUG_INPUT
  #include <sstream>
#endif

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace glm {

  std::ostream& operator<<(std::ostream& os, const glm::vec2& v) {
    os << "vec2( x: " << v.x << ", y: " << v.y << " )";
    return os;
  }

  std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    os << "vec3( x: " << v.x << ", y: " << v.y << ", z: " << v.z << " )";
    return os;
  }

} /* namespace glm */

namespace {

  using try_vec2_t = std::optional<glm::vec2>;

  const auto PIx2 = glm::pi<float>() * 2;
  const auto identity = glm::identity<glm::mat4>();

  struct сoordinate_t {
  public:
      enum { e_ax, e_ay, e_az, e_count };
  public:
      glm::vec4 axises[e_count] = { glm::vec4(ax, 0.0f), glm::vec4(ay, 0.0f), glm::vec4(az, 0.0f) };
      const сoordinate_t& rotate(const glm::mat4 val) {
        for(auto& it : axises)
          it = val * it;
        return *this;
      }
  public:
    static const glm::vec3 ax;
    static const glm::vec3 ay;
    static const glm::vec3 az;
    static const glm::vec3 zero;
  };

  const glm::vec3 сoordinate_t::ax = { 1.0f, 0.0f, 0.0f };
  const glm::vec3 сoordinate_t::ay = { 0.0f, 1.0f, 0.0f };
  const glm::vec3 сoordinate_t::az = { 0.0f, 0.0f, 1.0f };
  const glm::vec3 сoordinate_t::zero = { 0.0f, 0.0f, 0.0f };

  std::ostream& operator<<(std::ostream& os, const сoordinate_t& v) {
    os << "axis x: " << glm::vec3(v.axises[сoordinate_t::e_ax]) << std::endl
      << "axis y: " << glm::vec3(v.axises[сoordinate_t::e_ay]) << std::endl
      << "axis z: " << glm::vec3(v.axises[сoordinate_t::e_az]) << std::endl;
    return os;
  }
  
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
    return PIx2 * (std::mktime(&val) - ys) / (std::mktime(&tmp) - ys);
  }

  float get_rotation_position(std::tm val) {
    const std::time_t time = (val.tm_hour * 60 + val.tm_min) * 60 + val.tm_sec;
    return PIx2 * time / (24 * 60 * 60);
  }

#if DEBUG_INPUT
  idata_t get_user_data(const std::string& date, const float& latitude, const float& longitude, const float& at) {
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
    std::cout << "please input longitude [-180 ... 180]:";
    std::cin >> res.longitude;
    if(std::cin.fail() || res.longitude < -180.0f || res.longitude > 180.0f)
      throw std::invalid_argument("wrong input longitude.");
    res.longitude = glm::radians(res.longitude);
    std::cout << "please input  axial tilt [-90 ... 90] positive new year from samer other wise from winter: ";
    std::cin >> res.at;
    if(std::cin.fail() || res.at < -90.0f || res.at > 90.0f)
      throw std::invalid_argument("wrong input axial tilt.");
    res.at = glm::radians(res.at);
    return res;
  }
#endif

  std::pair<сoordinate_t, glm::mat4> get_sun_direction(const idata_t& v) {
    // https://en.wikipedia.org/wiki/Rotation_matrix
    // creating rotate matrix around axis Z. for calculate sunlight direction
    std::pair<сoordinate_t, glm::mat4> res;
    res.second = glm::rotate(identity, v.op, сoordinate_t::az);
    // https://en.wikipedia.org/wiki/Unit_vector
    // rotate unit vector by axis X arount axis Z
    res.first = сoordinate_t().rotate(res.second);
    return res;
  }

  сoordinate_t get_planet_point(const idata_t& v, const glm::mat4& mtx) {
    // crate coordinate system for planet point and rotate it light direction angle
    сoordinate_t pp = сoordinate_t().rotate(mtx);
    // crate rotate matrix around axis Z for longitude plus rotation period angle
    const auto lon = glm::rotate(identity, v.longitude + v.rpp, glm::vec3(pp.axises[сoordinate_t::e_az]));
    // rotate coordinate system for longitude plus rotation period angle
    pp.rotate(lon);
    // create rotare matrix arount axis y for latitude angle;
    const auto lat = glm::rotate(identity, v.latitude, glm::vec3(pp.axises[сoordinate_t::e_ay]));
    // get planet points depens of longitude plus rotation period and latitude.
    pp.rotate(lat);
    // create rotate matrix around axis Y on axial tilt angle
    const auto at = glm::rotate(identity, v.at, сoordinate_t::ay);
    // rotate planet point for axial tilt angle and return;
    return pp.rotate(at);
  }

  // if sunlight is not reachable for planet point then return empty object.
  try_vec2_t get_solar_panel_angle(const сoordinate_t& sd, const сoordinate_t& pp) {
    // https://en.wikipedia.org/wiki/Normal_(geometry)
    // Check up the illumination of a point planet and calculate normalе solar panel, and normalize it
    if(0.0f <= glm::dot(sd.axises[сoordinate_t::e_ax], pp.axises[сoordinate_t::e_ax]))
      return try_vec2_t();
    // calulate angle
    return try_vec2_t({glm::degrees(std::acos(glm::dot(glm::vec3(sd.axises[сoordinate_t::e_ay]), glm::vec3(pp.axises[сoordinate_t::e_ax])))),
      glm::degrees(std::acos(glm::dot(glm::vec3(sd.axises[сoordinate_t::e_az]), glm::vec3(pp.axises[сoordinate_t::e_ax]))))});
  }

} /* namespace */

int main(int ac, char* av[]) {
  try {
#if DEBUG_INPUT
    idata_t id = get_user_data("2020 01 01 00:00:00", -85.0f, 0.0f, -23.3f);
#else
    // request data from user
    const idata_t id = get_user_data();
#endif
    std::cout << id << std::endl;
    // get sun direction and rotate matrix
    const auto sd = get_sun_direction(id);
    std::cout << sd.first << std::endl;
    // get planet ponint depends of longitude, latitude, axial tilt, date, time
    const auto pp = get_planet_point(id, sd.second);
    std::cout << pp << std::endl;
    // calculate normal for solat panel
    if(const auto spa = get_solar_panel_angle(sd.first, pp))
      std::cout << "solar panel angle is " << *spa << std::endl;
    else
      std::cout << "planet point on the shadow side." << std::endl;
    return 0;
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 1;
}
