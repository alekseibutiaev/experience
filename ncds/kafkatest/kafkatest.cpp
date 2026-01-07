#include <ctime>

#include <mutex>
#include <thread>
#include <chrono>
#include <thread>
#include <string>
#include <memory>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <shared_mutex>

#include <nlohmann/json.hpp>

#include <librdkafka/rdkafkacpp.h>

#include <thread_pool.hpp>
#include <table_manager.h>
#include <accessor/config.h>
#include <accessor/avro_decode.h>
#include <accessor/consumer.h>
#include <accessor/sources/tools.h>
#include <sequence_manager.h>
#include <location.h>
#include <message.h>


// https://github.com/confluentinc/librdkafka/issues/2758
// f0592490d1c708e57805b71c04c451e69632c6b6

namespace {

  class read_json_t {
  public:
    read_json_t(const nlohmann::json& json)
      : m_json(json) {
    }
    nasdaq::string_try_t operator()(const std::string& val) const {
      return  m_json.contains(val) ? m_json[val].is_string() ?
        nasdaq::string_try_t(m_json[val]) : m_json[val].dump() : nasdaq::string_try_t();
    }
  private:
    const nlohmann::json& m_json;
  };

  union tracking_id_t {
    struct {
      long ts : 48;
      short ctr : 16;
    } data;
    long _long;
  };

  std::string time_print(const nasdaq::clock_t::time_point now = nasdaq::clock_t::now()) {
    static const char* format[] = {"%H:%M:%S", "%Y%m%d %H:%M:%S"};
    const auto frac = (std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % std::chrono::seconds(1)).count();
    const auto _now = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    std::ostringstream oss;
    std::tm time;
    localtime_r(&_now, &time);
    oss << std::put_time(&time, format[86400 < _now]) << '.'<< std::left <<
      std::setw(6) << std::setfill('0') << frac;
    return oss.str();
  }

  class my_data_t : public nasdaq::data_delegate_t {
  public:
    my_data_t(const nasdaq::time_point_t& tp, const std::string& stream, const std::string& msg,
         nasdaq::error_t& error, const bool show = false)
        : m_error(error)
        , m_show(show) {
      if(m_show)
        m_oss << time_print() << ", in " << time_print(tp) << ", stream: " << stream << ", message: " << msg;
    }
    ~my_data_t() {
      if(m_show)
        m_error.info(m_oss.str());
    }
    void data(const std::size_t& idx, const std::string& field, const std::string& value) override {
      if(m_show)
        m_oss << ", " << field << ": [" << value << ']';
    }
    void data(const std::size_t& idx, const std::string& field, const unsigned char& value) override {
      if(m_show)
        m_oss << ", " << field << ": [" << value << ']';
    }
    void data(const std::size_t& idx, const std::string& field, const int& value) override {
      if(m_show)
        m_oss << ", " << field << ": [" << value << ']';
    }
    void data(const std::size_t& idx, const std::string& field, const nasdaq::long_wrp_t& value) override {
      if(m_show)
        m_oss << static_cast<long>(value);
    }
    void data(const std::size_t& idx, const std::string& field, const float& value) override {
      if(m_show)
        m_oss << ", " << field << ": [" << value << ']';
    }
    void data(const std::size_t& idx, const std::string& field, const double& value) override {
      if(m_show)
        m_oss << ", " << field << ": [" << value << ']';
    }
    void data(const std::size_t& idx, const std::string& field, const bool& value) override  {
      if(m_show)
        m_oss << ", " << field << ": [" << value << ']';
    }
    void data(const std::size_t& idx, const std::string& field, const nasdaq::time_point_t& value) override {
      if(m_show)
        m_oss << ", " << time_print(value);
    }
  private:
    nasdaq::error_t& m_error;
    const bool m_show;
    std::ostringstream m_oss;
  };

  class deletate_t : public nasdaq::table_manager_t, public nasdaq::error_t {
  public:
    using sequence_manager_ptr = std::shared_ptr<nasdaq::sequence_manager_t>;
    using sequences_map_t = std::map<const std::string*, sequence_manager_ptr>;
  public:
    deletate_t(const nasdaq::get_property_t& get_property, const nasdaq::execute_t& executer,
          const bool enable = true)
        : m_get_property(get_property)
        , m_executer(executer)
        , m_enable(enable)
        , m_accum(0)
        , m_count(0) {
      m_get_property("test");
    }
  private:
    using oss_thread_t = std::map<std::thread::id, std::ostringstream>;
  private: // nasdaq::acc::table_manager_t
    void table(const std::string& stream, const std::string& msg, const nasdaq::fields_t& fields) override {
      nasdaq::table_manager_t::table(stream, msg, fields);
      std::ostringstream oss;
      oss << "stream: " << stream << ", msg: " << msg << " [";
      for(std::size_t i = 0; i < fields.size(); ++i)
        oss << (i == 0 ? "" : ", ") << fields[ i ];
      oss << ']' << __FILE_STR__ << std::endl;
      info(oss.str());
    }
    void record(const std::string& stream, const std::string& msg, const std::size_t& sn,
      const nasdaq::decoder_t& decoder, const nasdaq::record_ptr record, const nasdaq::time_point_t& tp) override {
#if 0
{
  std::ostringstream oss;
  oss << "[" << std::setw(8) << std::setfill('0') << sn << "]e";
  debug(oss.str());
}
#endif
      auto& fields = get_fields(stream, msg);
      if(fields.empty()) {
        std::ostringstream oss;
        oss << "unsuported message stream: " << stream << " message: " << msg;
        debug(oss.str());
        get_fields(stream, msg);
//        return;
      }
      if(auto message = nasdaq::message_t::create(stream, msg, sn, record, decoder, m_get_property,
          static_cast<nasdaq::table_manager_t&>(*this), static_cast<nasdaq::error_t&>(*this) , tp)) {
        const auto* topic_ptr = &message->topic();
        auto it = m_sequences_map.find(topic_ptr);
        if(it == m_sequences_map.end())
          it = m_sequences_map.emplace(std::make_pair(topic_ptr,
            std::make_shared<sequence_manager_ptr::element_type>(m_executer, std::bind(&deletate_t::consumer, this,  std::placeholders::_1), *this))).first;
#if 0
{
  std::ostringstream oss;
  oss << "[" << std::setw(8) << std::setfill('0') << sn << "]m";
  debug(oss.str());
}
#endif
//        it->second->push(std::move(message));
      }
      else {
#if 0
{
  std::ostringstream oss;
  oss << "[" << std::setw(8) << std::setfill('0') << sn << "]u" << " ";
  tools::pbuffer(msg.data(), msg.size(), oss);
  debug(oss.str());
}
#endif
      }
      show_delay(tp);
    }
    bool save(const std::string& stream, const std::string& schema) override {
      std::cout << std::string("write file:") + "./schema/" + stream + ".sch" << std::endl;
      return nasdaq::table_manager_t::save("./schema/" + stream + ".sch", schema);
    }
    std::string load(const std::string& stream) override {
      const std::string fname = "./schema/" + stream + ".sch";
      std::cout << std::string("read file: ") << fname << std::endl;
      return nasdaq::table_manager_t::load(fname);
    }
    void consumer(nasdaq::sequence_manager_t::messages_t& value) {
      std::ostringstream oss;
      oss << std::this_thread::get_id() << " received: " << value.size() << " messages";
      debug(oss.str());
    }
  private:
    void show_delay(const nasdaq::time_point_t& ts) {
#if 0
      m_accum += std::chrono::duration_cast<std::chrono::microseconds>(nasdaq::clock_t::now() - ts).count();
      if(0 == ++m_count % 1000 ) {
        info("averege delay: " + std::to_string(m_accum / 1000) + " microseconds" + __FILE_STR__);
        m_accum = 0;
      }
#endif
    }
    void debug(const std::string& msg) const {
      std::lock_guard _(m_lock_cout);
      std::cout << time_print() << " DEBUG: " << msg << std::endl;
    }
    void info(const std::string& msg) const  {
      std::lock_guard _(m_lock_cout);
      std::cout << time_print() << " INFO: " << msg << std::endl;
    }
    void warning(const std::string& msg) const  {
      std::lock_guard _(m_lock_cout);
      std::cout << time_print() << " WAGNING: " << msg << std::endl;
    }
    void error(const std::string& msg) const  {
      std::lock_guard _(m_lock_cout);
      std::cout << time_print() << " ERROR: " << msg << std::endl;
    }
  private:
    const nasdaq::get_property_t m_get_property;
    const nasdaq::execute_t& m_executer;
    sequences_map_t m_sequences_map;
    const bool m_enable;
    std::size_t m_accum;
    std::size_t m_count;
    mutable std::mutex m_lock_cout;
  };

  class rebalance_cb_t : public RdKafka::RebalanceCb {
  public:
    rebalance_cb_t() {}
    void rebalance_cb (RdKafka::KafkaConsumer *consumer, RdKafka::ErrorCode err,
        std::vector<RdKafka::TopicPartition*>&partitions) {
      std::cout << "rebalance_cb" << std::endl;
      return;
    }
  };

  class offset_commit_cb_t : public RdKafka::OffsetCommitCb {
  public:
    offset_commit_cb_t(rebalance_cb_t& rbc)
      : m_rbc(rbc) {
    }
    void offset_commit_cb(RdKafka::ErrorCode err, std::vector<RdKafka::TopicPartition *>& offsets) override {
      std::cout << RdKafka::err2str(err) << std::endl;
      for(auto offset : offsets) {
        std::cout << " \"topic\": \"" << offset->topic() << "\", " <<
          " partition: " << offset->partition() << " offset: " << offset->offset() <<
          (offset->err() ? " error: " + RdKafka::err2str(offset->err()) : "") << std::endl;
//          offset->set_offset(startOffset);
      }
    }
  private:
    rebalance_cb_t& m_rbc;
  };

} /* namespace */

int main(int ac, char* av[]) {
  
  int res = 0;
  try {
    std::cout << "test" << std::endl;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    std::vector<std::string> topics = {nasdaq::acc::avro_decoder_t::control};
    topics.insert(topics.end(), j["topics"].begin(), j["topics"].end());
    read_json_t rj(j);
    nasdaq::get_property_t getter(rj);

    rebalance_cb_t rdb;
    offset_commit_cb_t occb(rdb);

    tools::thread_pool_t<128> tread_pool;
    nasdaq::execute_t execute = [&tread_pool](std::function<void()> value) {
      tread_pool.execute(std::move(value));
    };

    deletate_t delegate(getter, execute, true);
    const nasdaq::error_t& error = delegate;
    nasdaq::table_manager_t& table_manager = delegate;
    nasdaq::acc::config_t cnf(getter, error);
    cnf.read_config(getter, error);
    cnf.set(&rdb, error);
    cnf.set(&occb, error);

    nasdaq::acc::avro_decoder_t decode(table_manager, error);
    nasdaq::acc::consumer_t consumer(cnf, getter, execute, decode, error);
    tread_pool.start();
    consumer.start(topics);
    for(std::size_t i = 0; i < 60;
#if 0
      ++i
#endif
    )
      std::this_thread::sleep_for(std::chrono::seconds(1));
    consumer.stop();
    tread_pool.stop();
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
    res = 1;
  }
  std::cout << "leave programm!! result: " << res << std::endl;
  return res;
}
