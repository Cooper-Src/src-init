#include "http_client.hpp"

#include <curl/curl.h>
#include <stdexcept>

namespace srcinit
{
    HttpClient::HttpClient()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    HttpClient::~HttpClient()
    {
        curl_global_cleanup();
    }

    size_t HttpClient::writeCallback(
        void* contents,
        size_t size,
        size_t nmemb,
        void* userp)
    {
        std::string* response =
            static_cast<std::string*>(userp);

        response->append(
            static_cast<char*>(contents),
            size * nmemb);

        return size * nmemb;
    }

    std::string HttpClient::get(
        const std::string& url)
    {
        CURL* curl = curl_easy_init();

        if (!curl)
        {
            throw std::runtime_error(
                "Failed to initialize CURL.");
        }

        std::string response;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // GitHub API requires a User-Agent.
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "src-init/0.1");

        // Follow redirects.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        CURLcode result =
            curl_easy_perform(curl);

        if (result != CURLE_OK)
        {
            curl_easy_cleanup(curl);

            throw std::runtime_error(
                curl_easy_strerror(result));
        }

        curl_easy_cleanup(curl);

        return response;
    }
}