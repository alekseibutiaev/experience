//
// Created by Spencer Sortman on 7/19/21.
//
#pragma once

#include <unordered_map>
#include <json-c/json.h>

#include "internal/utils/FindResources.h"

static constexpr const char* LOGGER = "logger";


static std::unordered_map<std::string, int> get_logger_configs() {
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *max_files_json;
    struct json_object *max_size_json;
    struct json_object *debug_json;

    std::string file_path = get_resource_path() + "logging.json";

    try {
        fp = std::fopen(file_path.c_str(), "r");
        std::size_t err = fread(buffer, 1024, 1, fp);
        (void)err;
        fclose(fp);
    }
    catch (std::exception &e) {
        std::string err_str = e.what();
        throw std::runtime_error("Unable to read from " + file_path + " : " + err_str);
    }

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "max_files", &max_files_json);
    json_object_object_get_ex(parsed_json, "max_size", &max_size_json);
    json_object_object_get_ex(parsed_json, "debug", &debug_json);

    int max_files = json_object_get_int(max_files_json);
    int max_size = json_object_get_int(max_size_json);
    int debug = json_object_get_int(debug_json);

    json_object_put(parsed_json);

    std::unordered_map<std::string, int> configs = {{"max_files", max_files},
                                                    {"max_size", max_size},
                                                    {"debug", debug}};

    return configs;
}