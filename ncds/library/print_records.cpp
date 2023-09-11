#include <map>
#include <iostream>
#include <fstream>

#include "print_records.h"

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

ostream_ptr get_stream(const std::string& name) {
  static std::map<std::string, std::size_t> idx;
  return std::make_shared<std::ofstream>((name + "_idx_" + std::to_string(idx[name]++) + ".text").c_str());
}

void print_records(const std::vector<avro::GenericRecord>& records, ostream_ptr os) {
  auto& outs = *os;
  for (auto &record : records) {
    outs << "Message name: " << record.schema()->name().simpleName() << std::endl;
    for (size_t i = 0; i < record.fieldCount(); i++) {
      avro::GenericDatum datum = record.fieldAt(i);
      outs << record.schema()->nameAt(i) << ": ";
      if (datum.type() == avro::AVRO_DOUBLE)
        outs << datum.value<double>() << std::endl;
      else if (datum.type() == avro::AVRO_LONG)
        outs << datum.value<int64_t>() << std::endl;
      else if (datum.type() == avro::AVRO_INT)
        outs << datum.value<int>() << std::endl;
      else if (datum.type() == avro::AVRO_STRING)
        outs << datum.value<std::string>() << std::endl;
    }
  }
}
