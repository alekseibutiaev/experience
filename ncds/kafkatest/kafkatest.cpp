#include <ctime>

#include <mutex>
#include <chrono>
#include <thread>
#include <string>
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

#include "../nasdaq/thread_pool.hpp"
#include "../nasdaq/config.h"
#include "../nasdaq/avro_decode.h"
#include "../nasdaq/consumer.h"
#include "../nasdaq/location.h"

// https://github.com/confluentinc/librdkafka/issues/2758

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

  class deletate_t : public nasdaq::avro_decode_t::delegate_t, public nasdaq::error_t {
  public:
    deletate_t(const bool enable = true)
        : m_enable(enable)
        , m_accum(0)
        , m_count(0) {
    }
  private:
    using msg_fields_t = std::map<std::string, nasdaq::avro_decode_t::delegate_t::fields_t>;
    using stream_msg_t = std::map<std::string, msg_fields_t>;
    using oss_thread_t = std::map<std::thread::id, std::ostringstream>;
  private:
    void table(const std::string& stream, const std::string& msg,
        const nasdaq::avro_decode_t::delegate_t::fields_t& fields) override {
      std::ostringstream oss;
      oss << "stream: " << stream << ", msg: " << msg << " [";
      for(std::size_t i = 0; i < fields.size(); ++i)
        oss << (i == 0 ? "" : ", ") << fields[ i ];
      oss << ']' << __FILE_STR__ << std::endl;
      info(oss.str());
      std::unique_lock _(m_lock_stream_msg);
      m_stream_msg[stream][msg] = fields;
    }
    void message(const nasdaq::avro_decode_t& decoder, const nasdaq::time_point_t& ts,
        const std::string& stream, const std::string& msg, const nasdaq::record_t record) override {
      const auto& filelds = get_fields(stream, msg);
      if(filelds.empty()) {
        std::cout << "unsuported message stream: " << stream << " message: " << msg << std::endl;
        return;
      }
      const std::size_t count = filelds.size();
      begin_msg(ts, stream, msg);
      for(std::size_t i = 0; i < count; ++i)
        decoder.get_field(record, i);
      end_msg();
      show_delay(ts);
    }

    bool save(const std::string& stream, const std::string& schema) {
      std::cout << std::string("write file:") + "./schema/" + stream + ".sch" << std::endl;
      return write("./schema/" + stream + ".sch", schema);
    }

    std::string load(const std::string& stream) {
      std::cout << std::string("read file: ") + "./schema/" + stream + ".sch" << std::endl;
      return read("./schema/" + stream + ".sch");
    }

    void begin_msg(const nasdaq::time_point_t& tp, const std::string& stream, const std::string& msg) {
      if(m_enable)
        [this]() -> std::ostream& {std::unique_lock _(m_lock_oss_thread); return (m_oss_thread[std::this_thread::get_id()]
          = std::move(std::ostringstream()));}() << time_print() << ", in " << time_print(tp) <<
          ", stream: " << stream << ", message: " << msg;
    }
    void end_msg() {
      if(m_enable)
        [this]{std::shared_lock _(m_lock_oss_thread); info(static_cast<std::ostringstream&>(m_oss_thread[std::this_thread::get_id()] <<
            __FILE_STR__ << std::endl).str());}();
    }
    void data(const std::string& field, const std::string& data) override {
      if(m_enable)
        [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}() <<
          ", " << field << ": " << data;
    }
    void data(const std::string& field, const unsigned char& data) override  {
      if(m_enable)
        [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}() <<
          ", " << field << ": " << data;
    }
    void data(const std::string& field, const int& data) override  {
      if(m_enable)
        [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}() <<
          ", " << field << ": " << data;
    }
    void data(const std::string& field, const long& data) override {
      if(m_enable) {
        std::ostream& os = [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}();
        os << ", " << field << ": ";
        if("uniqueTimestamp" == field || "trackingID" == field) {
          tracking_id_t val;
          val._long = data;
          os << time_print(nasdaq::clock_t::time_point(nasdaq::clock_t::duration(val.data.ts)));
        }
        else
          os << data;
      }
    }
    void data(const std::string& field, const float& data) override  {
      if(m_enable)
        [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}() <<
          ", " << field << ": " << data;
    }
    void data(const std::string& field, const double& data) override  {
      if(m_enable)
        [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}() <<
          ", " << field << ": " << data;
    }
    void data(const std::string& field, const bool& data) override  {
      if(m_enable)
        [this]() -> std::ostream& {std::shared_lock _(m_lock_oss_thread); return m_oss_thread[std::this_thread::get_id()];}() <<
          ", " << field << ": " << data;
    }
    const nasdaq::avro_decode_t::delegate_t::fields_t& get_fields(const std::string& stream,
        const std::string& msg) const {
      static const nasdaq::avro_decode_t::delegate_t::fields_t empty;
      std::shared_lock _(m_lock_stream_msg);
      auto it1 = m_stream_msg.find(stream);
      if(it1 == m_stream_msg.end())
        return empty;
      auto it2 = it1->second.find(msg);
      if(it2 == it1->second.end())
        return empty;
      return it2->second;
    }
  private:
    std::string time_print(const nasdaq::clock_t::time_point now = nasdaq::clock_t::now()) const {
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
    void show_delay(const nasdaq::time_point_t& ts) {
      m_accum += std::chrono::duration_cast<std::chrono::microseconds>(nasdaq::clock_t::now() - ts).count();
      if(0 == ++m_count % 1000 ) {
        info("averege delay: " + std::to_string(m_accum / 1000) + " microseconds" + __FILE_STR__);
        m_accum = 0;
      }
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
    const bool m_enable;
    std::size_t m_accum;
    std::size_t m_count;
    mutable std::mutex m_lock_cout;
    mutable std::shared_mutex m_lock_stream_msg;
    stream_msg_t m_stream_msg;
    mutable std::shared_mutex m_lock_oss_thread;
    oss_thread_t m_oss_thread;
    bool m_tmp;
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
    std::vector<std::string> topics = {nasdaq::avro_decode_t::control};
    topics.insert(topics.end(), j["topics"].begin(), j["topics"].end());

    rebalance_cb_t rdb;
    offset_commit_cb_t occb(rdb);
    deletate_t delegate(false);

    read_json_t rj(j);
    nasdaq::config_t cnf(rj, delegate);
    cnf.read_config(rj, delegate);
    cnf.set(&rdb, delegate);
    cnf.set(&occb, delegate);

    nasdaq::avro_decode_t decode(delegate, delegate);
    tools::thread_pool_t<128> tread_pool;
    nasdaq::consumer_t::execute_t execute = [&tread_pool](std::function<void()> value) {
      tread_pool.execute(std::move(value));
    };
    nasdaq::consumer_t consumer(cnf, rj, execute, decode, delegate);
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
