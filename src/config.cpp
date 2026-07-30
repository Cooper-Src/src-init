#include "config.hpp"

#include <cjson/cJSON.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace srcinit
{
    std::filesystem::path Config::configDirectory()
    {
        return std::filesystem::path(std::getenv("LOCALAPPDATA"))
            / "src-init";
    }

    std::filesystem::path Config::configFile()
    {
        return configDirectory() / "config.json";
    }

    bool Config::exists()
    {
        return std::filesystem::exists(configFile());
    }

    bool Config::saveGitHubToken(const std::string& token)
    {
        std::filesystem::create_directories(configDirectory());

        cJSON* root = cJSON_CreateObject();

        cJSON_AddStringToObject(
            root,
            "github_token",
            token.c_str());

        char* json = cJSON_Print(root);

        std::ofstream out(configFile());

        if (!out)
        {
            cJSON_Delete(root);
            cJSON_free(json);
            return false;
        }

        out << json;

        cJSON_Delete(root);
        cJSON_free(json);

        return true;
    }

    std::string Config::githubToken()
    {
        if (!exists())
        {
            return "";
        }

        std::ifstream in(configFile());

        if (!in)
        {
            return "";
        }

        std::stringstream buffer;
        buffer << in.rdbuf();

        cJSON* root =
            cJSON_Parse(buffer.str().c_str());

        if (!root)
        {
            return "";
        }

        std::string token;

        cJSON* item =
            cJSON_GetObjectItem(root, "github_token");

        if (cJSON_IsString(item))
        {
            token = item->valuestring;
        }

        cJSON_Delete(root);

        return token;
    }

    bool Config::removeGitHubToken()
    {
        if (!exists())
        {
            return true;
        }

        cJSON* root = cJSON_CreateObject();

        char* json = cJSON_Print(root);

        std::ofstream out(configFile());

        if (!out)
        {
            cJSON_Delete(root);
            cJSON_free(json);
            return false;
        }

        out << json;

        cJSON_Delete(root);
        cJSON_free(json);

        return true;
    }
}