#include <cstdlib>

#include "internal/utils/Oauth.h"


MemoryStruct::~MemoryStruct() {
  free(memory);
}

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
  char *ptr = static_cast<char *>(realloc(mem->memory, mem->size + realsize + 1));
  if(!ptr) {
      /* out of memory! */
      printf("not enough memory (realloc returned NULL)\n");
      return 0;
  }
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}

NCDSOAuthBearerTokenRefreshCb::NCDSOAuthBearerTokenRefreshCb(std::unordered_map<std::string, std::string> &security_cfg) {
    token_endpoint_uri = security_cfg[AuthenticationConfigLoader::OAUTH_TOKEN_ENDPOINT_URI];
    client_id = security_cfg[AuthenticationConfigLoader::OAUTH_CLIENT_ID];
    client_secret = security_cfg[AuthenticationConfigLoader::OAUTH_CLIENT_SECRET];
    post_fields = "grant_type=client_credentials&client_id="+client_id+"&client_secret="+client_secret;
}

void NCDSOAuthBearerTokenRefreshCb::oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string &oauthbearer_config) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = static_cast<char*>(malloc(1));  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */
    // HTTPS request for access token
    curl = curl_easy_init();
    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, token_endpoint_uri.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
      curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
      // set HTTP POST parameters
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, this->post_fields.c_str());

      res = curl_easy_perform(curl);

      curl_easy_cleanup(curl);

      std::string err_str = curl_easy_strerror(res);
      if (res != CURLE_OK) {
          throw std::runtime_error("Error retrieving token: " + err_str);
      }
    }

    struct json_object *jobj;
    struct json_object *j_access_token;
    struct json_object *j_expires_in;
    jobj = json_tokener_parse(chunk.memory);
    json_object_object_get_ex(jobj, "access_token", &j_access_token);
    json_object_object_get_ex(jobj, "expires_in", &j_expires_in);
    const char* access_token_char = json_object_get_string(j_access_token);
    if (!access_token_char) {
        throw std::runtime_error("Null token received");
    }
    std::string access_token = access_token_char;
    uint64_t token_lifetime = json_object_get_int64(j_expires_in);

    std::string errstr;
    errstr = "";

    //free(chunk.memory);
    json_object_put(jobj);

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    const std::list<std::string> extensions;
    RdKafka::ErrorCode tok_err = handle->oauthbearer_set_token(
      access_token,
      ms + token_lifetime * 1000, // expiry
      //"service-account-infrontasa-annika-norberg", //principal in java client logs
      "infrontasa-annika-norberg", // principal ? == user?
      extensions,                  // list of extensions
      errstr                       // string for writing the error message
    );
    //std::cerr << "set token callback: " << tok_err << " : " << errstr << std::endl;

    if (tok_err != RdKafka::ERR_NO_ERROR)
    {
        // std::cerr << "calling set_tok_failure because of: " << tok_err << " : " << errstr << std::endl;
        RdKafka::ErrorCode tok_failure_err = handle->oauthbearer_set_token_failure(errstr);
        if (tok_failure_err != RdKafka::ERR_NO_ERROR)
        {
        //    std::cerr << "set_tok_failure because of: " << tok_failure_err << " : " << errstr << std::endl;
            throw std::runtime_error("Token Error Occurred: " + errstr);
        }
    }
}
