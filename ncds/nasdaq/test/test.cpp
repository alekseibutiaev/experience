
#include <limits>
#include <array>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

#define BOOST_TEST_MODULE dom_test
#include <boost/test/unit_test.hpp>

#define protected public
#define private public

#include "../message.h"
#include "../decoder.h"
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

  template <std::size_t N>
  class msg_t : public nasdaq::message_t {
  public:
    msg_t(const nasdaq::message_t& value) : nasdaq::message_t(value) {}
  };

  const nasdaq::message_t::creators_t creators = {
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<0>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<1>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<2>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<3>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<4>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<5>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<6>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<7>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<8>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<9>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<10>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<11>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<12>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<13>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<14>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<15>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<16>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<17>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<18>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<19>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<20>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<21>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<22>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<23>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<24>>(value);},
    [](const nasdaq::message_t& value){return std::make_unique<msg_t<25>>(value);}
  };
#if 0
  template <std::size_t N>
  void fill(creators_t& creators) {
    if constexpr (N > 0)
        creators[N - 1] = [](const message_t& value) {return std::unique_ptr<message_t>(new msg_t<N - 1>(value));};
        fill<N - 1>(creators);
  }
#endif


  class config_t {
  public:
    config_t(const std::string& config)
      : m_json(nlohmann::json::parse(config)) {
    }
    nasdaq::string_try_t operator()(const std::string& path) const {
      const auto list = get_array(path, '/');
      std::reference_wrapper<const nlohmann::json> tmp = m_json;
      for(const auto& s : list)
        if(tmp.get().contains(s))
          tmp = tmp.get()[s];
        else
          return nasdaq::string_try_t();
      return nasdaq::string_try_t(tmp.get().template get<std::string>());      
    }
  private:
    const nlohmann::json m_json;
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

BOOST_AUTO_TEST_CASE(data_delegate_test) {
  const auto STRING = std::string("string");
  const auto BOOL = static_cast<bool>(1);
  const auto UCHAR = static_cast<unsigned char>(10);
  const auto INT = static_cast<int>(100);
  const auto LONG = static_cast<long>(1000);
  const auto FLOAT = static_cast<float>(10000);
  const auto DOUBLE = static_cast<double>(100000);
  const auto TIMEPOINT = nasdaq::clock_t::time_point(nasdaq::clock_t::duration(1000000));

  struct my_data_t : public nasdaq::data_delegate_t {
    void data(const std::size_t& idx, const std::string& field, const std::string& value) override {
      m_value = value;
    }
    void data(const std::size_t& idx, const std::string& field, const unsigned char& value) override {
      m_value = value;
    }
    void data(const std::size_t& idx, const std::string& field, const int& value) override {
      m_value = value;
    }
    void data(const std::size_t& idx, const std::string& field, const nasdaq::long_wrp_t& value) override {
      m_value = static_cast<long>(value);
    }
    void data(const std::size_t& idx, const std::string& field, const float& value) override {
      m_value = value;
    }
    void data(const std::size_t& idx, const std::string& field, const double& value) override {
      m_value = value;
    }
    void data(const std::size_t& idx, const std::string& field, const bool& value) override {
      m_value = value;
    }
    void data(const std::size_t& idx, const std::string& field, const nasdaq::time_point_t& value) override {
      m_value = value;
    }

    nasdaq::value_t m_value;
  } data;

  nasdaq::data_delegate_t &my_data = data;

std::cout << std::string("std::string") << std::endl;

  my_data.data(0, std::string("std::string"), std::string(STRING));
  BOOST_REQUIRE_NO_THROW(std::get<std::string>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_string>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<std::string>(data.m_value), STRING);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_string>(data.m_value), STRING);
  BOOST_REQUIRE_THROW(std::get<bool>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(data.m_value), std::bad_variant_access);

std::cout << std::string("unsigned char") << std::endl;

  my_data.data(0, std::string("unsigned char"), UCHAR);
  BOOST_REQUIRE_NO_THROW(std::get<unsigned char>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_bytes>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<unsigned char>(data.m_value), UCHAR);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_bytes>(data.m_value), UCHAR);
  BOOST_REQUIRE_THROW(std::get<bool>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(data.m_value), std::bad_variant_access);

std::cout << std::string("int") << std::endl;

  my_data.data(0, std::string("int"), INT);
  BOOST_REQUIRE_NO_THROW(std::get<int>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_int>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<int>(data.m_value), INT);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_int>(data.m_value), INT);
  BOOST_REQUIRE_THROW(std::get<bool>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(data.m_value), std::bad_variant_access);

std::cout << std::string("float") << std::endl;

  my_data.data(0, std::string("float"), FLOAT);
  BOOST_REQUIRE_NO_THROW(std::get<float>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_float>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<float>(data.m_value), FLOAT);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_float>(data.m_value), FLOAT);
  BOOST_REQUIRE_THROW(std::get<bool>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(data.m_value), std::bad_variant_access);

std::cout << std::string("double") << std::endl;

  my_data.data(0, std::string("double"), DOUBLE);
  BOOST_REQUIRE_NO_THROW(std::get<double>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_double>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<double>(data.m_value), DOUBLE);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_double>(data.m_value), DOUBLE);
  BOOST_REQUIRE_THROW(std::get<bool>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_boolean>(data.m_value), std::bad_variant_access);

std::cout << std::string("bool") << std::endl;

  my_data.data(0, std::string("bool"), BOOL);
  BOOST_REQUIRE_NO_THROW(std::get<bool>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_boolean>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<bool>(data.m_value), BOOL);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_boolean>(data.m_value), BOOL);
  BOOST_REQUIRE_THROW(std::get<std::string>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_string>(data.m_value), std::bad_variant_access);

std::cout << std::string("long") << std::endl;

  my_data.data(0, std::string("long"), LONG);
  BOOST_REQUIRE_NO_THROW(std::get<long>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_long>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<long>(data.m_value), LONG);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_long>(data.m_value), LONG);
  BOOST_REQUIRE_THROW(std::get<std::string>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_string>(data.m_value), std::bad_variant_access);

std::cout << std::string("uniqueTimestamp") << std::endl;

  my_data.data(0, std::string("uniqueTimestamp"), static_cast<const long&>(TIMEPOINT.time_since_epoch().count()));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::time_point_t>(data.m_value));
  BOOST_REQUIRE_NO_THROW(std::get<nasdaq::e_time_point>(data.m_value));
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::time_point_t>(data.m_value), TIMEPOINT);
  BOOST_REQUIRE_EQUAL(std::get<nasdaq::e_time_point>(data.m_value), TIMEPOINT);
  BOOST_REQUIRE_THROW(std::get<std::string>(data.m_value), std::bad_variant_access);
  BOOST_REQUIRE_THROW(std::get<nasdaq::e_string>(data.m_value), std::bad_variant_access);

std::cout << std::string("end") << std::endl;

}

BOOST_AUTO_TEST_CASE(message_test) {

  class my_decoder_t : public nasdaq::decoder_t {
  public:
    struct my_record_t : nasdaq::record_t {
      my_record_t()
          : m_values(11) {
        m_values[0] = false;
        m_values[1] = static_cast<unsigned char>(45);
        m_values[2] = "A";
        m_values[3] = false;
        m_values[4] = static_cast<unsigned char>(45);
        m_values[5] = std::numeric_limits<int>::min();
        m_values[6] = std::numeric_limits<long>::min();
        m_values[7] = std::numeric_limits<double>::min();
        m_values[8] = nasdaq::clock_t::time_point();
        m_values[9] = "TEST_STRING";

      }
      nasdaq::values_t m_values;
    };
    
  public:
    void operator()(const nasdaq::time_point_t& tp, const std::string& stream, const void* buf, const std::size_t size) const {
      (void)tp;
      (void)stream;
      (void)buf;
      (void)size;
    }
    void get_field(const nasdaq::record_ptr record, const std::size_t& idx, nasdaq::data_delegate_t& data) const {
      auto r = std::dynamic_pointer_cast<my_record_t>(record);
      if(0 == idx)
        data.data(idx, "0", std::get<0>(r->m_values[0]));
      if(1 == idx)
        data.data(idx, "1", std::get<1>(r->m_values[1]));
      if(2 == idx)
        data.data(idx, "2", std::get<6>(r->m_values[2]));
      if(3 == idx)
        data.data(idx, "3", std::get<0>(r->m_values[3]));
      if(4 == idx)
        data.data(idx, "4", std::get<1>(r->m_values[4]));
      if(5 == idx)
        data.data(idx, "5", std::get<2>(r->m_values[5]));
      if(6 == idx)
        data.data(idx, "6", std::get<3>(r->m_values[6]));
      if(7 == idx)
        data.data(idx, "7", std::get<4>(r->m_values[7]));
      if(8 == idx)
        data.data(idx, "8", std::get<5>(r->m_values[8]));
      if(9 == idx)
        data.data(idx, "9", std::get<6>(r->m_values[9]));
    }
  };

  const test_error_t error;

  const std::string njson = "{\"test\":{\"name_msg_type\":\"my_msgType\"}}";
  const std::string wjson = "{\"test\":{\"name_msg_tipe\":\"my_msgType\"}}";
  const std::string wjson1 = "{\"test\":{\"name_msg_type\":\"mymsgType\"}}";

  const nasdaq::message_t::module_info_t info = {creators, "test", "msgType"};
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
  BOOST_TEST_REQUIRE(0 != error.m_msg.find("msgType"));
  BOOST_REQUIRE_EQUAL(nasdaq::message_t::npos, nasdaq::message_t::get_type_idx(config_t(wjson1), info, npos, error));
  BOOST_TEST_REQUIRE(!error.m_msg.empty());
  BOOST_TEST_REQUIRE(0 != error.m_msg.find("mymsgType"));

  auto& stream_idx = nasdaq::message_t::m_stream_type_idx;

  BOOST_REQUIRE_EQUAL(0, nasdaq::message_t::msg_type_idx(config_t(njson), "stream1", info, fields0, error));
  BOOST_REQUIRE_EQUAL(1, nasdaq::message_t::m_stream_type_idx.size());
  BOOST_REQUIRE_EQUAL(0, nasdaq::message_t::m_stream_type_idx.find("stream1")->second);
  BOOST_REQUIRE_EQUAL(1, nasdaq::message_t::msg_type_idx(config_t(njson), "stream2", info, fields1, error));
  BOOST_REQUIRE_EQUAL(2, nasdaq::message_t::m_stream_type_idx.size());
  BOOST_REQUIRE_EQUAL(1, nasdaq::message_t::m_stream_type_idx.find("stream2")->second);
  BOOST_REQUIRE_EQUAL(0, nasdaq::message_t::msg_type_idx(config_t(njson), "stream1", info, fields1, error));
  BOOST_REQUIRE_EQUAL(2, nasdaq::message_t::m_stream_type_idx.size());
  BOOST_REQUIRE_EQUAL(0, nasdaq::message_t::m_stream_type_idx.find("stream1")->second);

  (void)stream_idx;

}

BOOST_AUTO_TEST_SUITE_END()  /* key_performance_test */
