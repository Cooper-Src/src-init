#pragma once

#include "repository_metadata.hpp"
#include "package_manifest.hpp"

namespace srcinit
{
    class ManifestGenerator
    {
    public:
        PackageManifest generate(
            const RepositoryMetadata& metadata);
    };
}