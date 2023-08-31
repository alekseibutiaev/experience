#pragma once

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <memory>

#include <curl/curl.h>
#include <json-c/json.h>

#include <librdkafka/rdkafkacpp.h>

#include "internal/utils/AuthenticationConfigLoader.h"

/**
\cond HIDE_FROM_DOCUMENTATION
*/
struct MemoryStruct {
  char *memory;
  size_t size;
  ~MemoryStruct();
};
/**
 * \endcond
 */

/**
\cond HIDE_FROM_DOCUMENTATION
*/
class NCDSOAuthBearerTokenRefreshCb : public RdKafka::OAuthBearerTokenRefreshCb {
public:
    NCDSOAuthBearerTokenRefreshCb(std::unordered_map<std::string, std::string> &security_cfg);
    void oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string &oauthbearer_config);
public:
    std::string token_endpoint_uri;
    std::string client_id;
    std::string client_secret;
    std::string post_fields;
};
/**
 * \endcond
 */
