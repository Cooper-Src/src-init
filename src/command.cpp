#include "command.hpp"
#include "version.hpp"
#include "http_client.hpp"
#include "github_provider.hpp"
#include "manifest_generator.hpp"
#include "manifest_writer.hpp"
#include "paths.hpp"

#include <iostream>

namespace srcinit
{
    int Command::run(int argc, char *argv[])
    {
        if (argc < 2)
        {
            return help();
        }

        std::string command = argv[1];

        std::vector<std::string> arguments;

        for (int i = 2; i < argc; ++i)
        {
            arguments.push_back(argv[i]);
        }

        if (command == "help")
            return help();

        if (command == "version")
            return version();

        if (command == "create")
            return create(arguments);

        std::cout << "Unknown command: " << command << '\n';
        return 1;
    }

    int Command::help()
    {
        std::cout
            << "src-init " << Version << "\n\n"
            << "Usage:\n"
            << "  src-init create <repository>\n"
            << "  src-init validate <manifest>\n"
            << "  src-init format <manifest>\n"
            << "  src-init update <manifest>\n"
            << "  src-init version\n"
            << "  src-init help\n";

        return 0;
    }

    int Command::version()
    {
        std::cout << Version << '\n';
        GitHubProvider github;
        ManifestGenerator generator;
        ManifestWriter writer;

        RepositoryMetadata repo =
            github.fetch(
                "https://github.com/raysan5/raylib");

        PackageManifest manifest =
            generator.generate(repo);

        writer.write(
            manifest,
            srcinit::Paths::registryDirectory() /
                (manifest.name + ".src"));
        return 0;
    }

    int Command::create(const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout << "Missing repository URL.\n";
            return 1;
        }

        GitHubProvider github;
        ManifestGenerator generator;
        ManifestWriter writer;

        RepositoryMetadata repo =
            github.fetch(arguments[0]);

        PackageManifest manifest =
            generator.generate(repo);

        auto output =
            srcinit::Paths::registryDirectory() /
            (manifest.name + ".src");

        writer.write(
            manifest,
            output);

        std::cout << "Created "
                  << output.make_preferred()
                  << '\n';

        return 0;
    }
}