
#include <limits>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

#define BOOST_TEST_MODULE dom_test
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../message.h"
#include "../types.h"
#include "../error.h"
#include "../location.h"

namespace {

  std::vector<std::string> get_array(const std::string& value, const char sep = ';') {
    std::vector<std::string> res;
    for(std::size_t from = 0, to = 0; to != std::string::npos && from < (to = value.find(sep, from)); from = to + 1)
      res.push_back(value.substr(from, to - from));
    return res;
  }

  class config_t {
  public:
    config_t(const std::string& config)
      : m_json(nlohmann::json::parse(config)) {
    }
    nasdaq::string_try_t operator()(const std::string& path) const {
      const auto& list = get_array(path, '/');
      nlohmann::json tmp = m_json;
      for(const auto& it : list)
        if(tmp.contains(it))
          tmp = tmp[it];
        else
          return nasdaq::string_try_t();
      return nasdaq::string_try_t(tmp.template get<std::string>());      
    }
  private:
    nlohmann::json m_json;
  };

  class test_error_t : public nasdaq::error_t {
  public:
    void debug(const std::string& msg) const { m_msg = msg; }
    void info(const std::string& msg) const  { m_msg = msg; }
    void warning(const std::string& msg) const { m_msg = msg; }
    void error(const std::string& msg) const { m_msg = msg; }
    mutable std::string m_msg;
  };

} /* namespace */

BOOST_AUTO_TEST_SUITE(static_test)

BOOST_AUTO_TEST_CASE(value_test) {

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

BOOST_AUTO_TEST_CASE(message_test) {

  const test_error_t error;

  const std::string njson = "{\"test\":{\"name_msg_type\":\"my_msgType\"}}";
  const std::string wjson = "{\"test\":{\"name_msg_tipe\":\"my_msgType\"}}";

  const nasdaq::message_t::creator_map_t cm;
  const nasdaq::message_t::module_info_t info = {cm, "test", "msgType"};
  const nasdaq::fields_t fields0 = {"my_msgType", "field0", "field1", "msgType"};
  const nasdaq::fields_t fields1 = {"field0", "my_msgType", "field1", "msgType"};
  const nasdaq::fields_t fields2 = {"field0", "field1", "my_msgType", "msgType"};
  const nasdaq::fields_t fields3 = {"my_msgType", "field0", "field1", "msgType"};
  const nasdaq::fields_t npos = {"my_msgType", "field0", "field1", "msg_type"};

  BOOST_REQUIRE_EQUAL(0, nasdaq::message_t::get_type_idx(config_t(njson), info, fields0, error));
  BOOST_TEST_REQUIRE(error.m_msg.empty());
  BOOST_REQUIRE_EQUAL(1, nasdaq::message_t::get_type_idx(config_t(njson), info, fields1, error));
  BOOST_TEST_REQUIRE(error.m_msg.empty());
  BOOST_REQUIRE_EQUAL(2, nasdaq::message_t::get_type_idx(config_t(njson), info, fields2, error));
  BOOST_TEST_REQUIRE(error.m_msg.empty());
  BOOST_REQUIRE_EQUAL(3, nasdaq::message_t::get_type_idx(config_t(wjson), info, fields3, error));
  BOOST_TEST_REQUIRE(error.m_msg.empty());
  BOOST_REQUIRE_EQUAL(nasdaq::message_t::npos, nasdaq::message_t::get_type_idx(config_t(wjson), info, npos, error));
  BOOST_TEST_REQUIRE(!error.m_msg.empty());

#if 0
  nasdaq::dom::get_type_idx::m_idx = std::numeric_limits<std::size_t>::max();
  BOOST_REQUIRE_EQUAL(1, nasdaq::dom::get_type_idx()(congif_t(njson), fields));
  BOOST_REQUIRE_EQUAL(nasdaq::dom::get_type_idx::m_idx, 1);
  nasdaq::dom::get_type_idx::m_idx = std::numeric_limits<std::size_t>::max();
  BOOST_REQUIRE_EQUAL(2, nasdaq::dom::get_type_idx()(congif_t(njson), fields));
  BOOST_REQUIRE_EQUAL(nasdaq::dom::get_type_idx::m_idx, 2);
  nasdaq::dom::get_type_idx::m_idx = std::numeric_limits<std::size_t>::max();
  BOOST_REQUIRE_EQUAL(0, nasdaq::dom::get_type_idx()(congif_t(wjson), fields));
  BOOST_REQUIRE_EQUAL(nasdaq::dom::get_type_idx::m_idx, 0);
  nasdaq::dom::get_type_idx::m_idx = std::numeric_limits<std::size_t>::max();
#endif

#if 0

  struct error_t : public nasdaq::error_t {
    void debug(const std::string& msg) const { m_msg = msg; }
    void info(const std::string& msg) const { m_msg = msg; }
    void warning(const std::string& msg) const { m_msg = msg; }
    void error(const std::string& msg) const { m_msg = msg; }
    mutable std::string m_msg;
  };

  BOOST_REQUIRE_NO_THROW({
    error_t error;
    nasdaq::record_t r([v = std::string("4")](const std::string&){return nasdaq::string_try_t(v);}, error);
    BOOST_REQUIRE_EQUAL(nasdaq::record_t::m_idx_type, 4);
    BOOST_TEST_REQUIRE(error.m_msg.empty());
    nasdaq::record_t::m_idx_type = std::numeric_limits<std::size_t>::max();
  });
  BOOST_REQUIRE_NO_THROW({
    error_t error;
    nasdaq::record_t r([v = std::string("5 ")](const std::string&){return nasdaq::string_try_t(v);}, error);
    BOOST_REQUIRE_EQUAL(nasdaq::record_t::m_idx_type, 5);
    BOOST_TEST_REQUIRE(error.m_msg.empty());
    nasdaq::record_t::m_idx_type = std::numeric_limits<std::size_t>::max();
  });
  BOOST_REQUIRE_NO_THROW({
    error_t error;
    nasdaq::record_t r([v = std::string("X ")](const std::string&){return nasdaq::string_try_t(v);}, error);
    BOOST_REQUIRE_EQUAL(nasdaq::record_t::m_idx_type, 2);
    BOOST_TEST_REQUIRE(!error.m_msg.empty());
    nasdaq::record_t::m_idx_type = std::numeric_limits<std::size_t>::max();
  });
#endif

}

BOOST_AUTO_TEST_SUITE_END()  /* key_performance_test */
