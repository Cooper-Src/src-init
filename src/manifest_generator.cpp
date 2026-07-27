#include "manifest_generator.hpp"

namespace srcinit
{
    PackageManifest ManifestGenerator::generate(
        const RepositoryMetadata &metadata)
    {
        PackageManifest manifest;

        manifest.name = metadata.name;
        manifest.version = metadata.version;
        manifest.description = metadata.description;

        manifest.source.type = "git";
        manifest.source.url = metadata.sourceUrl;
        manifest.source.branch = metadata.defaultBranch;

        manifest.license.name = metadata.license;

        manifest.homepage.url = metadata.homepage;

        return manifest;
    }
}