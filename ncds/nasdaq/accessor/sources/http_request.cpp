#include "http_request.h"

namespace nasdaq {

  namespace acc {

    http_request_t::curl_init_t::curl_init_t() {
      curl_global_init(CURL_GLOBAL_ALL);
    }

    http_request_t::curl_init_t::~curl_init_t() {
      curl_global_cleanup();
    } 

    http_request_t::http_request_t(const std::string& url, long timeout) :
      m_headers(0) {
      m_curl = curl_easy_init();
      curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeout);
      curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    }

    http_request_t::~http_request_t() {
      if(m_headers)
        curl_slist_free_all(m_headers);
      curl_easy_cleanup(m_curl);
    }

    void http_request_t::ssl_verify_peer(int value) {
      curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER , value);
    }

    void http_request_t::ssl_verify_host(int value) {
      curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST , value);
    }

    http_request_t::replay_t http_request_t::post(const std::string& msg) {
      replay_t res;
      if(!msg.empty())
        curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, msg.c_str());
      curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &res.second);
      /*const auto r = */curl_easy_perform(m_curl);
      curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &res.first);
      return res;
    }

    void http_request_t::append_header(const char* value) {
      m_headers = curl_slist_append(m_headers, value);
    }

    void http_request_t::append_header(const std::string& value) {
      append_header(value.c_str());
    }

    void http_request_t::append_headers() const {
    }

    size_t http_request_t::callback(char *ptr, size_t sz, size_t nmemb, std::string *s) {
      const size_t n = sz * nmemb;
      s->insert(s->end(), ptr, ptr + n);
      return n;
    }

  } /* namespace acc */

} /* namespace nasdaq */
