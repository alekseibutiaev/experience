//
// Created by Spencer Sortman on 9/23/21.
//
#pragma once

#include <memory>
#include <iosfwd>
#include <vector>

#include <avro/GenericDatum.hh>

using ostream_ptr = std::shared_ptr<std::ostream>;

void pbuffer(const void* buf, const std::size_t& size);

ostream_ptr get_stream(const std::string& name = "file_");

// This implementation might need to change based on the types of data in your records
void print_records(const std::vector<avro::GenericRecord>&records, ostream_ptr os);

