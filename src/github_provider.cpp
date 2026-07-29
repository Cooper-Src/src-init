#include "github_provider.hpp"
#include "http_client.hpp"

#include <stdexcept>
#include <iostream>
#include <cjson/cJSON.h>

namespace srcinit
{
    bool GitHubProvider::parseRepositoryUrl(
        const std::string &url,
        std::string &owner,
        std::string &repo)
    {
        const std::string prefix = "https://github.com/";

        if (!url.starts_with(prefix))
        {
            return false;
        }

        std::string path = url.substr(prefix.length());

        std::size_t slash = path.find('/');

        if (slash == std::string::npos)
        {
            return false;
        }

        owner = path.substr(0, slash);
        repo = path.substr(slash + 1);

        // Remove trailing ".git" if present.
        if (repo.ends_with(".git"))
        {
            repo.erase(repo.size() - 4);
        }

        return true;
    }

    RepositoryMetadata GitHubProvider::fetch(
        const std::string &repositoryUrl)
    {
        std::string owner;
        std::string repo;

        if (!parseRepositoryUrl(repositoryUrl, owner, repo))
        {
            throw std::runtime_error("Invalid GitHub repository URL.");
        }

        RepositoryMetadata metadata =
            fetchRepository(owner, repo);

         metadata.owner = owner;
        metadata.repository = repo;
        
            metadata.version =
            fetchLatestVersion(owner, repo);

        metadata.defaultTag =
            metadata.version;

        // metadata.defaultCommit =
        //     fetchCommitForTag(
        //         owner,
        //         repo,
        //         metadata.defaultTag);
        return metadata;
    }

    std::string GitHubProvider::fetchLatestVersion(
        const std::string &owner,
        const std::string &repo)
    {
        HttpClient client;

        std::string json =
            client.get(
                "https://api.github.com/repos/" +
                owner + "/" +
                repo +
                "/releases/latest");

        cJSON *root =
            cJSON_Parse(json.c_str());

        if (!root)
            return "unknown";

        std::string version = "unknown";

        if (auto *tag =
                cJSON_GetObjectItem(root, "tag_name");
            cJSON_IsString(tag))
        {
            version = tag->valuestring;
        }

        cJSON_Delete(root);

        return version;
    }

    RepositoryMetadata GitHubProvider::fetchRepository(
        const std::string &owner,
        const std::string &repo)
    {
        HttpClient client;

        std::string json =
            client.get(
                "https://api.github.com/repos/" +
                owner + "/" + repo);

        cJSON *root = cJSON_Parse(json.c_str());

        if (!root)
            throw std::runtime_error("Failed to parse JSON.");

        RepositoryMetadata metadata;

        // name
        if (auto *item = cJSON_GetObjectItem(root, "name");
            cJSON_IsString(item))
            metadata.name = item->valuestring;

        // description
        if (auto *item = cJSON_GetObjectItem(root, "description");
            cJSON_IsString(item))
            metadata.description = item->valuestring;

        // clone_url
        if (auto *item = cJSON_GetObjectItem(root, "clone_url");
            cJSON_IsString(item))
            metadata.cloneUrl = item->valuestring;

        // default_branch
        if (auto *item = cJSON_GetObjectItem(root, "default_branch");
            cJSON_IsString(item))
            metadata.defaultBranch = item->valuestring;

        // homepage
        if (auto *item = cJSON_GetObjectItem(root, "homepage");
            cJSON_IsString(item))
            metadata.homepage = item->valuestring;

        // license.spdx_id
        if (auto *license = cJSON_GetObjectItem(root, "license"))
        {
            if (auto *spdx = cJSON_GetObjectItem(license, "spdx_id");
                cJSON_IsString(spdx))
            {
                metadata.license = spdx->valuestring;
            }
        }

        cJSON_Delete(root);

        return metadata;
    }
}