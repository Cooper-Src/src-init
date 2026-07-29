#pragma once

#include <string>

namespace srcinit
{
    struct RepositoryMetadata
    {
        std::string name;
        std::string version;
        std::string description;

        std::string cloneUrl;
        std::string defaultBranch;
        std::string defaultTag;
        std::string defaultCommit;

        std::string homepage;
        std::string license;

        std::string owner;
        std::string repository;

        RepositoryMetadata fetchRepository(
            const std::string &owner,
            const std::string &repo);

        std::string fetchLatestVersion(
            const std::string &owner,
            const std::string &repo);

        std::string fetchCommitForTag(
            const std::string &owner,
            const std::string &repo,
            const std::string &tag);
    };
}