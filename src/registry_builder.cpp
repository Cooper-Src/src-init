#include "registry_builder.hpp"
#include "paths.hpp"

#include <cjson/cJSON.h>

#include <filesystem>
#include <fstream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

namespace srcinit
{
    int RegistryBuilder::build()
    {
        std::vector<std::string> manifests;

        for (const auto &entry :
             fs::directory_iterator(Paths::registryDirectory()))
        {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".src")
                continue;

            manifests.push_back(
                entry.path().filename().string());
        }

        std::sort(
            manifests.begin(),
            manifests.end());

        cJSON *root =
            cJSON_CreateObject();

        cJSON_AddNumberToObject(
            root,
            "version",
            1);

        cJSON *array =
            cJSON_AddArrayToObject(
                root,
                "manifests");

        for (const auto &file : manifests)
        {
            cJSON_AddItemToArray(
                array,
                cJSON_CreateString(
                    file.c_str()));
        }

        char *json =
            cJSON_Print(root);

        fs::path output =
            Paths::registryDirectory()
                .parent_path() /
            "index.json";

        std::ofstream out(output);

        if (!out)
        {
            return -1;
        }

        out << "{\n";
        out << "    \"version\": 1,\n";
        out << "    \"manifests\": [\n";

        for (std::size_t i = 0; i < manifests.size(); ++i)
        {
            out << "        \"" << manifests[i] << "\"";

            if (i + 1 != manifests.size())
            {
                out << ",";
            }

            out << "\n";
        }

        out << "    ]\n";
        out << "}\n";

        out.close();

        return static_cast<int>(manifests.size());
    }
}