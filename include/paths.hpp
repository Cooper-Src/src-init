#pragma once

#include <filesystem>

namespace srcinit
{
    class Paths
    {
    public:
        static std::filesystem::path registryDirectory();
    };
}