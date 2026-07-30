#include "command.hpp"
#include "version.hpp"
#include "http_client.hpp"
#include "github_provider.hpp"
#include "manifest_generator.hpp"
#include "manifest_writer.hpp"
#include "paths.hpp"
#include "config.hpp"
#include "registry_builder.hpp"

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

        if (command == "auth")
            return auth(arguments);

        if (command == "registry")
            return registry(arguments);

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
    int Command::auth(
        const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout
                << "Usage:\n"
                << "  src-init auth login\n"
                << "  src-init auth status\n"
                << "  src-init auth logout\n";

            return 1;
        }

        if (arguments[0] == "login")
        {
            std::string token;

            std::cout
                << "GitHub Personal Access Token:\n> ";

            std::getline(std::cin, token);

            if (Config::saveGitHubToken(token))
                std::cout << "Token saved.\n";
            else
                std::cout << "Failed to save token.\n";

            return 0;
        }

        if (arguments[0] == "status")
        {
            if (Config::githubToken().empty())
                std::cout
                    << "GitHub authentication not configured.\n";
            else
                std::cout
                    << "GitHub authentication configured.\n";

            return 0;
        }

        if (arguments[0] == "logout")
        {
            Config::removeGitHubToken();

            std::cout
                << "Token removed.\n";

            return 0;
        }

        return 1;
    }
    int Command::registry(
        const std::vector<std::string> &arguments)
    {
        if (arguments.empty())
        {
            std::cout
                << "Usage:\n"
                << "  src-init registry build\n";

            return 1;
        }

        if (arguments[0] != "build")
        {
            std::cout
                << "Unknown registry command.\n";

            return 1;
        }

        RegistryBuilder builder;

        int packages = builder.build();

        if (packages < 0)
        {
            std::cout
                << "Failed to build registry.\n";

            return 1;
        }

        std::cout
            << "Registry index generated successfully.\n\n"
            << "Packages : " << packages << '\n'
            << "Output   : "
            << (Paths::registryDirectory().parent_path() / "index.json").make_preferred()
            << '\n';

        return 0;
    }
}