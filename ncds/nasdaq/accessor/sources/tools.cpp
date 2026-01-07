#include <map>
#include <iostream>
#include <fstream>

#include <avro/GenericDatum.hh>

#include "tools.h"

namespace tools {

  ostream_ptr get_stream(const std::string& name) {
    static std::map<std::string, ostream_ptr> streams;
    if(!streams[name])
      streams[name] = std::make_shared<std::ofstream>(("./text/" + name + ".text").c_str());
    return streams[name];
  }

  ostream_ptr get_stream_bin(const std::string& name, std::ios_base::openmode mode) {
    return std::make_shared<std::ofstream>(("./text/" + name + ".text").c_str(), mode);
  }

  void printcfg(const std::list<std::string>& value, std::ostream& os) {
    std::size_t idx = 0;
    for(const auto& it : value)
      os << it << (idx++ % 2 == 0 ?  '=' : '\n');
  }

  void pbuffer(const void* buf, const std::size_t& size, std::ostream& os) {
    char hex[128] = {0};
    char ch[17] = {0};
    for(std::size_t i = 0; i < size; ++i) {
      sprintf(&hex[(i % 16) * 5], "0x%02X ", reinterpret_cast<const unsigned char*>(buf)[i]);
      sprintf(&ch[(i % 16)], "%c", std::isprint(reinterpret_cast<const unsigned char*>(buf)[i]) ?
        reinterpret_cast<const unsigned char*>(buf)[i] : '.');
      if(0 == (i + 1) % 16)
        os << hex << ch << std::endl;
    }
    if(size % 16)
      os << hex << ch << std::endl;
  }

  void print_records(const nasdaq::acc::avro_record_t& record, std::ostream& os) {
    os << "Message: " << record.first->schema()->name().simpleName() << ' ';
    for(size_t i = 0; i < record.first->fieldCount(); i++) {
      avro::GenericDatum datum = record.first->fieldAt(i);
      os << record.first->schema()->nameAt(i) << ": ";
      if (datum.type() == avro::AVRO_DOUBLE)
        os << datum.value<double>() << ' ';
      else if (datum.type() == avro::AVRO_LONG)
        os << datum.value<int64_t>() << ' ';
      else if (datum.type() == avro::AVRO_INT)
        os << datum.value<int>() << ' ';
      else if (datum.type() == avro::AVRO_STRING)
        os << datum.value<std::string>() << ' ';
    }
    os << std::endl;
  }

} /* namespace tools */
