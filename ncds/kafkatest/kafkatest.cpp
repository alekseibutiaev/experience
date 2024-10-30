
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <stdexcept>
#include <functional>

#include <nlohmann/json.hpp>

#include <librdkafka/rdkafkacpp.h>

#include <config.h>
#include <avro_decode.h>
#include <consumer.h>

// https://github.com/confluentinc/librdkafka/issues/2758

namespace {

  class read_json_t {
  public:
    read_json_t(const nlohmann::json& json)
      : m_json(json) {
    }
    kf::string_try_t operator()(const std::string& val) const {
      return  m_json.contains(val) ? m_json[val].is_string() ?
        kf::string_try_t(m_json[val]) : m_json[val].dump() : kf::string_try_t();
    }
  private:
    const nlohmann::json& m_json;
  };

  void err(const std::string& value) {
    std::cout << "configuration error: " << value << std::endl;
  }

  union tracking_id_t {
    struct {
      long ts : 48;
      short ctr : 16;
    } data;
    long _long;
  };

  std::string get_time(const long ntime) {
    static const char* gmt = "GMT";
    static std::time_t midnight = 0;
    if(!midnight) {
      struct tm time;
      std::time_t t = std::time(0);
      localtime_r(&t, &time);
      time.tm_sec = time.tm_min = time.tm_hour = time.tm_gmtoff = 0;
      time.tm_zone = gmt;
      midnight = mktime(&time);
      std::time_t t1 = t - t % 86400;

      return std::string();
    }
    return std::string();
  }

  std::ostream& operator<< (std::ostream& os, const tracking_id_t val) {
    // (ctr: 0, ts: 59996231542528 sec: 59996 mil: 59996231 mic: 59996231542)
    auto mic = val.data.ts / 1000;
    auto mil = mic / 1000;
    auto sec = mil / 1000;
    os << " ( ctr: " << val.data.ctr << ", ts: " << val.data.ts <<
      " sec: " << sec << " mil: " << mil << " mic: " << mic <<  " )";
  }

  class deletate_t : public kf::avro_decode_t::delegate_t {
  public:
    deletate_t(const bool enable = true)
        : m_enable(enable) {
    }
  private:
    using msg_fields_t = std::map<std::string, kf::avro_decode_t::delegate_t::fields_t>;
    using stream_msg_t = std::map<std::string, msg_fields_t>;
  private:
    void table(const std::string& stream, const std::string& msg,
        const kf::avro_decode_t::delegate_t::fields_t& fields) override {
      std::cout << "stream: " << stream << ", msg: " << msg << " [";
      for(std::size_t i = 0; i < fields.size(); ++i)
        std::cout << (i == 0 ? "" : ", ") << fields[ i ];
      std::cout << ']' << std::endl;
      m_stream_msg[stream][msg] = fields;
    }
    void message(const kf::avro_decode_t& decoder, const std::string& stream, const std::string& msg,
        const kf::avro_decode_t::record_ptr record) override {
      const auto& filelds = get_fields(stream, msg);
      if(filelds.empty()) {
        std::cout << "unsuported message stream: " << stream << " message: " << msg << std::endl;
        return;
      }
      begin_msg(stream, msg);
      for(std::size_t i = 0; i < filelds.size(); ++i)
        decoder.get_field(record, i);
      end_msg();
    }
    void begin_msg(const std::string& stream, const std::string& msg) override {
      if(m_enable)
        std::cout << "stream: " << stream << ", message: " << msg;
    }
    void end_msg() override {
      if(m_enable) std::cout << std::endl;
    }
    void data(const std::string& field, const std::string& data) override {
      if(m_enable) std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const unsigned char& data) override  {
      if(m_enable) std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const int& data) override  {
      if(m_enable) std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const long& data) override  {
      if(m_enable) std::cout << ", " << field << ": ";
      if("uniqueTimestamp" == field || "trackingID" == field) {
        tracking_id_t val;
        val._long = data;
        if(m_enable) std::cout << val;
      }
      else
        /*std::cout << data*/;
    }
    void data(const std::string& field, const float& data) override  {
      if(m_enable) std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const double& data) override  {
      if(m_enable) std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const bool& data) override  {
      if(m_enable) std::cout << " " << field << ": " << data;
    }
    const kf::avro_decode_t::delegate_t::fields_t& get_fields(const std::string& stream, const std::string& msg) const {
      static const kf::avro_decode_t::delegate_t::fields_t empty;
      auto it1 = m_stream_msg.find(stream);
      if(it1 == m_stream_msg.end())
        return empty;
      auto it2 = it1->second.find(msg);
      if(it2 == it1->second.end())
        return empty;
      return it2->second;
    }
  private:
    const bool m_enable;
    stream_msg_t m_stream_msg;

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
          " error: " << (offset->err() ? RdKafka::err2str(offset->err()) : "") << std::endl;
//          offset->set_offset(startOffset);
      }

      return;
    }
  private:
    rebalance_cb_t& m_rbc;
  };

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    std::vector<std::string> topics = {kf::avro_decode_t::control};
    topics.insert(topics.end(), j["topics"].begin(), j["topics"].end());

    rebalance_cb_t rdb;
    offset_commit_cb_t occb(rdb);

    deletate_t d(true);

    read_json_t rj(j);
    kf::config_t cnf;
    cnf.read_config(rj, err);
    cnf.set(&rdb, err);
    cnf.set(&occb, err);
    kf::consumer_t consumer(cnf, rj, err);
    const std::string cms = j["control_message_schema"];
    kf::avro_decode_t decode(d/*, cms*/);
    consumer.consume(topics, decode);
    for(;;)
      std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}
