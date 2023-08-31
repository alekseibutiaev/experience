//
// Created by Spencer Sortman on 9/23/21.
//
#pragma once

#include <vector>
#include <avro/GenericDatum.hh>

// This implementation might need to change based on the types of data in your records
void print_records(std::vector<avro::GenericRecord> &records);