#include "manifest_writer.hpp"

#include <fstream>

namespace srcinit
{
    bool ManifestWriter::write(
        const PackageManifest &manifest,
        const std::filesystem::path &path)
    {
        std::ofstream out(path);

        if (!out)
        {
            return false;
        }

        out << "name = " << manifest.name << '\n';
        out << "version = " << manifest.version << '\n';
        out << "description = " << manifest.description << "\n\n";

        out << "[source]\n";
        out << "type = " << manifest.source.type << '\n';
        out << "url = " << manifest.source.url << '\n';
        out << "branch = " << manifest.source.branch << "\n\n";

        out << "[license]\n";
        out << "name = " << manifest.license.name << "\n\n";

        out << "[homepage]\n";
        out << "url = " << manifest.homepage.url << '\n';

        return true;
    }
}