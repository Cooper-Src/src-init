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

        manifest.source.type = "archive";
manifest.source.format = "zip";

if (!metadata.defaultTag.empty())
{
    manifest.source.url =
        "https://github.com/" +
        metadata.owner +
        "/" +
        metadata.repository +
        "/archive/refs/tags/" +
        metadata.defaultTag +
        ".zip";
}
else
{
    manifest.source.url =
        "https://github.com/" +
        metadata.owner +
        "/" +
        metadata.repository +
        "/archive/refs/heads/" +
        metadata.defaultBranch +
        ".zip";
}

        manifest.license.name = metadata.license;

        manifest.homepage.url = metadata.homepage;

        return manifest;
    }
}