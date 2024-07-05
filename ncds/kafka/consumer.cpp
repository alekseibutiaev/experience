#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <stdexcept>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include <config.h>
#include <consumer.h>
//#include <print_records.h>
#include <internal/utils/SeekToMidnight.h>

#include <avro/Generic.hh>
#include <avro/Decoder.hh>
#include <avro/Stream.hh>
#include <avro/GenericDatum.hh>
#include <avro/Specific.hh>

#include "oauthbearer.h"
#include "event.h"

namespace {

  kf::config_t clone_config(const kf::config_t& config, const kf::error_t& notify) {
    if(kf::config_t::e_global != config.get_type())
      throw(std::runtime_error("config is not a global"));
    return config.clone(notify);
  }

  void pbuffer(const void* buf, const std::size_t& size) {
    char hex[128] = {0};
    char ch[17] = {0};
    for(std::size_t i = 0; i < size; ++i) {
      sprintf(&hex[(i % 16) * 5], "0x%02X ", reinterpret_cast<const unsigned char*>(buf)[i]);
      sprintf(&ch[(i % 16)], "%c", std::isprint(reinterpret_cast<const unsigned char*>(buf)[i]) ?
        reinterpret_cast<const unsigned char*>(buf)[i] : '.');
      if(0 == (i + 1) % 16)
        std::cout << hex << ch << std::endl;
    }
    if(size % 16)
      std::cout << hex << ch << std::endl;
  }


  void print_records(const std::vector<avro::GenericRecord>& records, std::ostream& os) {
    for (auto &record : records) {
      os << "Message name: " << record.schema()->name().simpleName() << std::endl;
      for (size_t i = 0; i < record.fieldCount(); i++) {
        avro::GenericDatum datum = record.fieldAt(i);
        os << record.schema()->nameAt(i) << ": ";
        if (datum.type() == avro::AVRO_DOUBLE)
          os << datum.value<double>() << std::endl;
        else if (datum.type() == avro::AVRO_LONG)
          os << datum.value<int64_t>() << std::endl;
        else if (datum.type() == avro::AVRO_INT)
          os << datum.value<int>() << std::endl;
        else if (datum.type() == avro::AVRO_STRING)
          os << datum.value<std::string>() << std::endl;
      }
    }
  }


} /* namespace */

namespace kf {

  consumer_t::consumer_t(const config_t& config, const get_property_t& get_property, const error_t& notify)
      : m_config(clone_config(config, notify))
      , m_get_property(get_property)
      , m_auth(std::make_shared<oauthbearer_t>(get_property))
      , m_event(std::make_shared<event_t>()) {
    config.print();
    std::cout << "conf" << std::endl;
    m_config.set(m_auth.get(), notify);
//    m_config.set(m_event.get(), notify);
    rd_kafka_conf_set_log_cb(m_config.get_config()->c_ptr_global(), logger);
    m_config.print();
  }

  const std::string topics[] = {"TOTALVIEW.stream"/*, "QBBO-A-BSX.stream", "NLSCTA.stream"*/};

  void consumer_t::test(const avro::ValidSchema& schema) {
    static std::size_t count = 0;
    if(const auto topic = m_get_property("topic")) {
      std::string err;
      m_consumer.reset(RdKafka::KafkaConsumer::create(m_config.get_config(), err));
      std::vector<RdKafka::TopicPartition*> part;
      for(const auto& it : topics) {
        part.push_back(RdKafka::TopicPartition::create(it, 0, RdKafka::Topic::OFFSET_END));
        m_topic_partitions.push_back(topic_partition_ptr(part.back()));
      }
      m_consumer->assign(part);
      std::string offset;
      m_config.get("auto.offset.reset", offset);
      std::cout << offset << std::endl;
      if (offset == "earliest" || offset == "smallest" || offset == "beginning") {
        for(auto& it : m_topic_partitions)
          seek_to_midnight_at_past_day(m_consumer.get(), it.get(), 0);
      }

      avro::DecoderPtr decoder = avro::binaryDecoder();
      std::size_t idx = 0;
      for(;;) {
        std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(m_consumer->consume(10000));
        if(0 >= msg->payload())
          continue;
        std::cout << msg->topic_name() << std::endl;
        pbuffer(msg->payload(), msg->len());
        auto data = std::make_shared<avro::GenericDatum>(schema);
        auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(msg->payload()), msg->len());
        decoder->init(*in);
        avro::decode(*decoder, *data);
        auto r = data->value<avro::GenericRecord>();
        print_records({r}, std::cout);


#if 0
        std::stringstream ss;
        ss << "./message/" << msg->topic_name() << '_' << std::setfill('0') << std::setw(8) << idx++ << ".msg";
        if(auto ofs = std::ofstream(ss.str(), std::ios_base::binary))
          ofs.write(reinterpret_cast<const char*>(msg->payload()), msg->len());
#endif
//        get_stream_bin("buf_" + std::to_string(count++), std::ios_base::binary)->write(reinterpret_cast<char*>(msg->payload()), msg->len());
/*        
        auto in = avro::memoryInputStream(static_cast<uint8_t *>(msg->payload()), msg->len());
        d->init(*in);
        avro::ValidSchema sch(schema);
        avro::GenericDatum datum(sch);
        avro::decode(*d, datum);
        std::cout << "Type: " << datum.type() << std::endl;
*/
/*
        avro::GenericRecord r = datum.value<avro::GenericRecord>();
        print_records({r}, std::cout);
*/
      }
    }
    else {
      std::cout << "topic unuavaqilable: " << std::endl;
    }
  }

  void consumer_t::logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf) {
    if(level == 7)
      return;
    std::cout << "Pounter: 0x" << std::hex << rk << std::dec << " level " << level << " " << fac <<
      " " << buf << std::endl;
  }

} /* namespace kf */
