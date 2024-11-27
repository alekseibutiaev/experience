
#include <iostream>

#define BOOST_TEST_MODULE stoporder_test
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "dom/dom_types.h"
#include "../location.h"

BOOST_AUTO_TEST_SUITE(static_test)

BOOST_AUTO_TEST_CASE(value_t_test) {

  const bool BOOL = false;
  const unsigned char BYTES = static_cast<unsigned char>('U');
  const int INT = 77777;
  const long LONG = 9090909;
  const double DOUBLE = 875.32458;
  const nasdaq::time_point_t TIME = nasdaq::clock_t::now();
  const std::string STRING = __FILE_STR__;

  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<bool, std::variant_alternative_t<nasdaq::e_boolean, nasdaq::value_t>>));
  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<unsigned char, std::variant_alternative_t<nasdaq::e_bytes, nasdaq::value_t>>));
  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<int, std::variant_alternative_t<nasdaq::e_int, nasdaq::value_t>>));
  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<long, std::variant_alternative_t<nasdaq::e_long, nasdaq::value_t>>));
  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<double, std::variant_alternative_t<nasdaq::e_double, nasdaq::value_t>>));
  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<nasdaq::time_point_t, std::variant_alternative_t<nasdaq::e_time_point, nasdaq::value_t>>));
  BOOST_TEST_REQUIRE(static_cast<bool>(std::is_same_v<std::string, std::variant_alternative_t<nasdaq::e_string, nasdaq::value_t>>));
  BOOST_REQUIRE_EQUAL(std::variant_size_v<nasdaq::value_t>, nasdaq::e_count);

  nasdaq::value_t value;

  value = BOOL;
  BOOST_REQUIRE_EQUAL(std::get<bool>(value), BOOL);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_boolean>(value), BOOL);
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_boolean>(value));
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_int>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<std::string>(value), std::bad_variant_access);

  value = !BOOL;
  BOOST_REQUIRE_EQUAL(std::get<bool>(value), !BOOL);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_boolean>(value), !BOOL);
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_boolean>(value));
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_long>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::time_point_t>(value), std::bad_variant_access);

  value = BYTES;
  BOOST_REQUIRE_EQUAL(std::get<unsigned char>(value), BYTES);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_bytes>(value), BYTES);
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_bytes>(value));
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::time_point_t>(value), std::bad_variant_access);

  value = INT;
  BOOST_REQUIRE_EQUAL(std::get<int>(value), INT);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_int>(value), INT);
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_int>(value));
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::time_point_t>(value), std::bad_variant_access);

  value = LONG;
  BOOST_REQUIRE_EQUAL(std::get<long>(value), LONG);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_long>(value), LONG);
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_long>(value));
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::time_point_t>(value), std::bad_variant_access);

  value = DOUBLE;
  BOOST_REQUIRE_EQUAL(std::get<double>(value), DOUBLE);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_double>(value), DOUBLE);
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_double>(value));
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::time_point_t>(value), std::bad_variant_access);

  value = TIME;
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::time_point_t>(value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_time_point>(value));
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::time_point_t>(value), TIME);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_time_point>(value), TIME);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<std::string>(value), std::bad_variant_access);

  value = STRING;
  BOOST_REQUIRE_NO_THROW(std::get<std::string>(value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_string>(value));
  BOOST_REQUIRE_EQUAL(std::get<std::string>(value), STRING);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_string>(value), STRING);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<bool>(value), std::bad_variant_access);

}

BOOST_AUTO_TEST_SUITE_END()  /* key_performance_test */
