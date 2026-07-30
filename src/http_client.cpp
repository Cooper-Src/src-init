#include "http_client.hpp"
#include "config.hpp"

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
        void *contents,
        size_t size,
        size_t nmemb,
        void *userp)
    {
        std::string *response =
            static_cast<std::string *>(userp);

        response->append(
            static_cast<char *>(contents),
            size * nmemb);

        return size * nmemb;
    }

    std::string HttpClient::get(
        const std::string &url)
    {
        CURL *curl = curl_easy_init();

        if (!curl)
        {
            throw std::runtime_error(
                "Failed to initialize CURL.");
        }

        std::string response;
        struct curl_slist *headers = nullptr;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // GitHub API requires a User-Agent.
        headers = curl_slist_append(
            headers,
            "User-Agent: src-init");

        std::string token =
            Config::githubToken();

        if (!token.empty())
        {
            headers = curl_slist_append(
                headers,
                ("Authorization: Bearer " + token).c_str());
        }

        curl_easy_setopt(
            curl,
            CURLOPT_HTTPHEADER,
            headers);

        // Follow redirects.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        CURLcode result =
            curl_easy_perform(curl);

        if (result != CURLE_OK)
        {
            if (headers)
            {
                curl_slist_free_all(headers);
            }

            curl_easy_cleanup(curl);

            throw std::runtime_error(
                curl_easy_strerror(result));
        }

        return response;
    }
}