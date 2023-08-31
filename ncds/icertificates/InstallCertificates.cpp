//
// Created by Spencer Sortman on 9/7/21.
//

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <json-c/json.h>


static const std::string kafka_cert_url = "https://tgbstk5716.execute-api.us-east-1.amazonaws.com/v1/get-certificate";


size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void install_cert(std::string &one_time_url, std::string &cert_path) {
    auto curl = curl_easy_init();

    CURLcode res;

    std::string response_string;
    std::string header_string;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, one_time_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            throw std::runtime_error(curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }


    std::ofstream out(cert_path);
    if (!out.good()) {
        throw std::runtime_error("Could not open stream to path: " + cert_path);
    }

    out << response_string;
    out.close();
}


std::string get_one_time_url() {
    auto curl = curl_easy_init();

    CURLcode res;

    std::string response_string;
    std::string header_string;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, kafka_cert_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            throw std::runtime_error(curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    json_object *jobj = json_tokener_parse(response_string.c_str());
    json_object *obj_url = json_object_object_get(jobj, "one_time_url");
    const char *url_val = json_object_get_string(obj_url);

    std::string url_str = url_val;
    json_object_put(jobj);

    return url_str;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " /path/to/certfile.crt" << std::endl;
        return 1;
    }

    std::string cert_path = argv[1];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    std::string url = get_one_time_url();
    install_cert(url, cert_path);

    curl_global_cleanup();
    return 0;
}