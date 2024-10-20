//
// Created by Spencer Sortman on 9/23/21.
//
#pragma once

#include <memory>
#include <iosfwd>
#include <list>

namespace avro {

  class GenericRecord;

} /* namespace avro */

#include <avro/GenericDatum.hh>

namespace tools {

  using ostream_ptr = std::shared_ptr<std::ostream>;

  ostream_ptr get_stream(const std::string& name = "file_");

  ostream_ptr get_stream_bin(const std::string& name, std::ios_base::openmode mode);

  void printcfg(const std::list<std::string>& value, std::ostream& os);

  void pbuffer(const void* buf, const std::size_t& size, std::ostream& os);

  // This implementation might need to change based on the types of data in your records
  void print_records(const std::shared_ptr<avro::GenericRecord>&record, std::ostream& os);

} /* namespace tools */
