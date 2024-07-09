//
// Created by Spencer Sortman on 9/23/21.
//
#pragma once

#include <memory>
#include <iosfwd>
#include <vector>
#include <list>

#include <avro/GenericDatum.hh>

using ostream_ptr = std::shared_ptr<std::ostream>;

void printcfg(const std::list<std::string>& value, std::ostream& os);

void pbuffer(const void* buf, const std::size_t& size, std::ostream& os);

ostream_ptr get_stream(const std::string& name = "file_");

ostream_ptr get_stream_bin(const std::string& name, std::ios_base::openmode mode);

// This implementation might need to change based on the types of data in your records
void print_records(const std::vector<avro::GenericRecord>&records, std::ostream& os);

