//
// Created by Jennifer Wang on 7/22/21.
//

#ifndef TEST_INTEGRATION_AUTHENTICATIONCONFIGLOADER_H
#define TEST_INTEGRATION_AUTHENTICATIONCONFIGLOADER_H

#include <librdkafka/rdkafkacpp.h>
#include <unordered_map>
#include <spdlog/spdlog.h>

/**
 * @ingroup internal
 * \defgroup utils utils
 * Utility classes and functions for the Nasdaq Cloud Data Service C++ SDK.
 * @{
 */

/**
 * @brief Utility to load the auth configuration parameters.
 */
class AuthenticationConfigLoader {
private:
    std::shared_ptr<spdlog::logger> logger;

public:
    AuthenticationConfigLoader();
    const static std::string OAUTH_TOKEN_ENDPOINT_URI;
    const static std::string OAUTH_CLIENT_ID;
    const static std::string OAUTH_CLIENT_SECRET;
    const static std::string OAUTH_USERNAME_CLAIM;
    static std::unordered_map<std::string, std::string> load_auth_config();
    std::string get_client_id(std::unordered_map<std::string, std::string> &cfg);
    void  add_nasdaq_specific_properties(std::unordered_map<std::string, std::string>  &cfg);
    bool validate_security_config(std::unordered_map<std::string, std::string> &cfg);
};

/**@}*/
#endif //TEST_INTEGRATION_AUTHENTICATIONCONFIGLOADER_H
