//
// Created by Spencer Sortman on 9/23/21.
//
#include <memory>
#include <string>
#include <unordered_map>

std::unique_ptr<RdKafka::Conf> get_kafka_config();

std::unordered_map<std::string, std::string> get_auth_config();