#pragma once

#include <filesystem>

#include "package_manifest.hpp"

namespace srcinit
{
    class ManifestWriter
    {
    public:
        bool write(
            const PackageManifest &manifest,
            const std::filesystem::path &path);
    };
}