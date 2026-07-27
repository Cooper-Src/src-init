#pragma once

#include <string>

namespace srcinit
{
    struct Source
    {
        std::string type;
        std::string url;
        std::string branch;
    };

    struct License
    {
        std::string name;
    };

    struct Homepage
    {
        std::string url;
    };

    struct PackageManifest
    {
        std::string name;
        std::string version;
        std::string description;

        Source source;
        License license;
        Homepage homepage;
    };
}