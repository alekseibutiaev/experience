#include <iostream>
#include <stdexcept>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include <config.h>
#include <consumer.h>
#include <print_records.h>
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

  void consumer_t::test(const avro::ValidSchema& schema) {
    static std::size_t count = 0;
    if(const auto topic = m_get_property("topic")) {
      std::string err;
      m_topic_partition.reset(RdKafka::TopicPartition::create(*topic + ".stream", 0, RdKafka::Topic::OFFSET_END));
      m_consumer.reset(RdKafka::KafkaConsumer::create(m_config.get_config(), err));
      m_consumer->assign({m_topic_partition.get()});
//      m_consumer->subscribe({"TOTALVIEW.stream"});
      std::string offset;
      m_config.get("auto.offset.reset", offset);
      std::cout << offset << std::endl;
      if (offset == "earliest" || offset == "smallest" || offset == "beginning")
        seek_to_midnight_at_past_day(m_consumer.get(), m_topic_partition.get(), 0);

      avro::DecoderPtr d = avro::binaryDecoder();
      for(;;) {
        std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(m_consumer->consume(10000));
        if(0 >= msg->payload())
          continue;
        pbuffer(msg->payload(), msg->len());
        get_stream_bin("buf_" + std::to_string(count++), std::ios_base::binary)->write(reinterpret_cast<char*>(msg->payload()), msg->len());
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

  }

  void consumer_t::logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf) {
    if(level == 7)
      return;
    std::cout << "Pounter: 0x" << std::hex << rk << std::dec << " level " << level << " " << fac <<
      " " << buf << std::endl;
  }

} /* namespace kf */
