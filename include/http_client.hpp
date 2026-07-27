#pragma once

#include <string>

namespace srcinit
{
    class HttpClient
    {
    public:
        HttpClient();
        ~HttpClient();

        std::string get(const std::string& url);

    private:
        static size_t writeCallback(
            void* contents,
            size_t size,
            size_t nmemb,
            void* userp);
    };
}