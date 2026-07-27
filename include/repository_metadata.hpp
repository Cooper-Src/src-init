#pragma once

#include <string>

namespace srcinit
{
    struct RepositoryMetadata
{
    std::string name;
    std::string version;
    std::string description;

    std::string sourceUrl;
    std::string homepage;
    std::string license;
    std::string defaultBranch;
};
}