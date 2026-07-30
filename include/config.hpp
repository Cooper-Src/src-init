#pragma once

#include <filesystem>
#include <string>

namespace srcinit
{
    class Config
    {
    public:
        static std::filesystem::path configDirectory();
        static std::filesystem::path configFile();

        static bool exists();

        static bool saveGitHubToken(
            const std::string& token);

        static std::string githubToken();

        static bool removeGitHubToken();
    };
}