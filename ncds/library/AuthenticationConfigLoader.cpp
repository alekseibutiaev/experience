//
// Created by Jennifer Wang on 7/22/21.
//

#include <unordered_map>

#include <spdlog/spdlog.h>

#include "internal/Logging.h"
#include "internal/utils/AuthenticationConfigLoader.h"
#include "internal/utils/TestConfigLoader.h"

const std::string AuthenticationConfigLoader::OAUTH_TOKEN_ENDPOINT_URI = "oauth.token.endpoint.uri";
const std::string AuthenticationConfigLoader::OAUTH_CLIENT_ID = "oauth.client.id";
const std::string AuthenticationConfigLoader::OAUTH_CLIENT_SECRET = "oauth.client.secret";
const std::string AuthenticationConfigLoader::OAUTH_USERNAME_CLAIM = "oauth.username.claim";

AuthenticationConfigLoader::AuthenticationConfigLoader() {
    logger = spdlog::get(LOGGER);
}

std::unordered_map<std::string, std::string> AuthenticationConfigLoader::load_auth_config() {
    std::unordered_map<std::string, std::string> auth_config = load_test_auth_config();
    return auth_config;
}

std::string AuthenticationConfigLoader::get_client_id(std::unordered_map<std::string, std::string>  &cfg) {
  if (cfg.empty())
      logger->warn("Missing config!");
  std::string client_id = cfg[AuthenticationConfigLoader::OAUTH_CLIENT_ID];
  return client_id;
}

void AuthenticationConfigLoader::add_nasdaq_specific_properties(std::unordered_map<std::string, std::string> &properties) {
  properties[AuthenticationConfigLoader::OAUTH_USERNAME_CLAIM] = "preferred_username";
}

bool AuthenticationConfigLoader::validate_security_config(std::unordered_map<std::string, std::string> &cfg) {
  AuthenticationConfigLoader::add_nasdaq_specific_properties(cfg);

  if (cfg.find(AuthenticationConfigLoader::OAUTH_TOKEN_ENDPOINT_URI) == cfg.end() || cfg[AuthenticationConfigLoader::OAUTH_TOKEN_ENDPOINT_URI].empty()) {
      logger->warn("Authentication Setting : {} Missing", AuthenticationConfigLoader::OAUTH_TOKEN_ENDPOINT_URI);
  }
  if (cfg.find(AuthenticationConfigLoader::OAUTH_CLIENT_ID)== cfg.end() || cfg[AuthenticationConfigLoader::OAUTH_CLIENT_ID].empty()) {
      logger->warn("Authentication Setting : {} Missing", AuthenticationConfigLoader::OAUTH_CLIENT_ID);
  }
  if (cfg.find(AuthenticationConfigLoader::OAUTH_CLIENT_SECRET)== cfg.end() || cfg[AuthenticationConfigLoader::OAUTH_CLIENT_SECRET].empty()) {
      logger->warn("Authentication Setting : {} Missing",  AuthenticationConfigLoader::OAUTH_CLIENT_SECRET);
  }
  if (cfg.find(AuthenticationConfigLoader::OAUTH_USERNAME_CLAIM)== cfg.end() || cfg[AuthenticationConfigLoader::OAUTH_USERNAME_CLAIM].empty()) {
      logger->warn("Authentication Setting : {} Missing",  AuthenticationConfigLoader::OAUTH_USERNAME_CLAIM);
  }
  return true;
}
