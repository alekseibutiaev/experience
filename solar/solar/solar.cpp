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

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <ctime>

#include <map>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace glm {

  std::ostream&  operator<<(std::ostream& os, const glm::vec3& v) {
    os << "vec3( x: " << v.x << ", y: " << v.y << ", z: " << v.z << " )";
    return os;
  }

} /* namespace glm */

namespace {

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
    tmp.tm_isdst = -1;
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

  idata_t get_user_data() {
#define DEBUG_INPUT 1
    std::tm tm = {0};
    idata_t res = {0};
#if DEBUG_INPUT
    std::istringstream iss("2020 06 12 00:00:00");
    iss >> std::get_time(&tm, "%Y %m %d %T");
#else
    std::cout << "Please input data in format YYYY mm[01 ... 12] dd[01 ... 31] HH[00 ... 23]:MM[00 ... 59]:SS[00 ... 60] ";
    std::cin >> std::get_time(&tm, "%Y %m %d %T");
#endif
    if(std::cin.fail())
      throw std::invalid_argument("wrong input data.");
    res.op = get_orbital_position(tm);
    res.rpp = get_rotation_position(tm);
#if DEBUG_INPUT
    res.latitude = glm::radians(58.0f);
    res.longitude = glm::radians(0.0f);
    res.at = glm::radians(23.3f);
#else
    std::cout << "please input latitude [-90 ... 90]: ";
    std::cin >> res.latitude;
    if(std::cin.fail() || res.latitude < -90.0f || res.latitude > 90.0f)
      throw std::invalid_argument("wrong input data.");
    res.latitude = glm::radians(res.latitude);
    std::cout << "please input longitude [-180 ... 180]: ";
    std::cin >> res.longitude;
    if (std::cin.fail() || res.longitude < -180.0f || res.longitude > 180.0f)
      throw std::invalid_argument("wrong input data.");
    res.longitude = glm::radians(res.longitude);
    std::cout << "please input  Axial tilt [-90 ... 90] negative new year from samer other wise from winter: ";
    std::cin >> res.at;
    if (std::cin.fail() || res.at < -90.0f || res.at > 90.0f)
      throw std::invalid_argument("wrong input data.");
    res.at = glm::radians(res.at);
#endif
    return res;
#undef DEBUG_INPUT
  }

} /* namespace */

int main( int ac, char* av[] ) {
  try {
    std::cout << "Hello World!" << std::endl;
    glm::vec3 v(1.1, 3.5, 2.34);
    std::cout << v << std::endl;
    const idata_t id = get_user_data();
    std::cout << id << std::endl;
    const auto lv = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) - glm::rotate(glm::mat4(1.0f), id.op, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    std::cout << lv << std::endl;

    return 0;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 1;
}
