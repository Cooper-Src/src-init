#pragma once

#include <string>

#include "repository_metadata.hpp"

namespace srcinit
{
    class GitHubProvider
{
public:
    RepositoryMetadata fetch(const std::string& repositoryUrl);

private:
    bool parseRepositoryUrl(
        const std::string& url,
        std::string& owner,
        std::string& repo);

    RepositoryMetadata fetchRepository(
        const std::string& owner,
        const std::string& repo);

    std::string fetchLatestVersion(
        const std::string& owner,
        const std::string& repo);
};
}