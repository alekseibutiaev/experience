#pragma once

#include <list>
#include <string>

#include <curl/curl.h>

namespace nasdaq {

  namespace acc {

    class http_request_t {
    public:
      using replay_t = std::pair<long, std::string>;
    public:
      http_request_t(const std::string& url, long timeout = 30 * 1000);
      ~http_request_t();
      void ssl_verify_peer(int value);
      void ssl_verify_host(int value);
      replay_t post(const std::string& msg = std::string());

      template  <typename... TT>
      void set_headers(TT&&... headers) {
        if (m_headers) {
          curl_slist_free_all(m_headers);
          m_headers = nullptr;
        }
        append_headers(std::forward<TT>(headers)...);
        curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
      }
    private:
      class curl_init_t {
        public:
        curl_init_t();
        ~curl_init_t();
      };
    private:
      void append_header(const char *header);
      void append_header(const std::string &header);
      void append_headers() const;
      template <typename T>
      void append_header(const std::list<T> &items) {
        for (auto item: items)
          append_header(item);
      }

      template  <typename T, typename... TT>
      void append_headers(T &&header, TT&&... headers) {
        append_header(std::forward<T>(header));
        append_headers(std::forward<TT>(headers)...);
      }
    private:
      static size_t callback(char *ptr, size_t sz, size_t nmemb, std::string *s);
    private:
      curl_init_t m_init;
      CURL* m_curl;
      curl_slist* m_headers = 0;
    };

  } /* namespace acc */

} /*namespace tools */

