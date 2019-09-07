#include <string>
#include <exception>
#include <functional>
#include <iostream>

#include <nlohmann/json.hpp>

const std::string _js = "{\"test\": \"value\"}";
 
const std::string js = "{\"name1\": \"value1\"}{\"name2\": \"val";
const std::string js1 = "ue2\"}{\"name3\": \"value3\"}{\"name4\": \"value4\",\"tast\": {\"n4\": \"v4\"}}{\"name5\": \"value5\"}";
const std::string js2 = "{\"name1\": \"value1\"}{\"name2\": \"value2\"}{\"name3\": \"value3\"}{\"name4\": \"value4\",\"tast\": {\"n4\": \"v4\"}}{\"name5\": \"value5\"}";
const std::string js3 = "{\"name1\": \"value1\"}{\"name2\": \"value2\"}{\"name3\": \"value3\"}{\"name4\": \"value4\",\"tast\": {\"n";
const std::string js4 = "4\": \"v4\"}}{\"name5\": \"value5\"}";

class msg_t {
public:
  using jsmsg_handle_t = std::function<void(nlohmann::json)>;
public:
  void apply(std::string msg) {
    m_msg += msg;
    for(;;) {
      try {
        m_finished = false;
        m_json.parse(m_msg, std::bind(&msg_t::parse_cb, this,
          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      }
      catch(const nlohmann::json::parse_error pe) {
        if(!m_finished)
          break;
        m_msg = m_msg.substr(pe.byte - 1);
        continue;
      }
      catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
      }
      break;
    }
  }
public:
    jsmsg_handle_t m_handle;
private:
  bool parse_cb(int depth, nlohmann::json::parse_event_t event, nlohmann::json& parsed) {
    switch(event) {
      case nlohmann::json::parse_event_t::object_start : // - `object_start`: the parser read `{` and started to process a JSON object
        break;
      case nlohmann::json::parse_event_t::key :          // - `key`: the parser read a key of a value in an object
        break;
      case nlohmann::json::parse_event_t::object_end : {  // - `object_end`: the parser read `}` and finished processing a JSON object
        if(0 == depth){
          if(m_handle)
            m_handle(std::move(parsed));
          else
            parsed.clear();
          m_finished = true;
        }
        break;
      }
      case nlohmann::json::parse_event_t::array_start :  // - `array_start`: the parser read `[` and started to process a JSON array
        break;
      case nlohmann::json::parse_event_t::array_end :    // - `array_end`: the parser read `]` and finished processing a JSON array
        break;
      case nlohmann::json::parse_event_t::value :        // - `value`: the parser finished reading a JSON value
        break;
    }
    return true;
  }
private:
  bool m_finished;
  nlohmann::json m_json;
  std::string m_msg;
};

struct js_handle {
  void operator()(nlohmann::json j) {
    std::cout << "new message" << std::endl;
    std::cout << j.dump(4) << std::endl;
  }
};

int main(int ac, char* av[]) {
  std::cout << "project" << std::endl;
  msg_t msg;
  msg.m_handle = js_handle();
  msg.apply(js3);
  msg.apply(js4);
  return 0;
}
