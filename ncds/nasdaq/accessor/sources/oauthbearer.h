#pragma once

#include <librdkafka/rdkafkacpp.h>

#include "accessor/acc_types.h"

namespace nasdaq {

  namespace acc {

      class oauthbearer_t : public RdKafka::OAuthBearerTokenRefreshCb {
      public:
        oauthbearer_t(const get_property_t& get_property);
      private:
        void oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string& oauthbearer_config) override;
      private:
        const std::string m_uri;
        const std::string m_glient_id;
        const std::string m_secret;
        const get_property_t m_get_property;
      };

  } /* namespace acc */

} /* namespace nasdaq */