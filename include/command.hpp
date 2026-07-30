#pragma once

#include <string>
#include <vector>

namespace srcinit
{
    class Command
    {
    public:
        int run(int argc, char* argv[]);

    private:
    int create(const std::vector<std::string>& arguments);
    int auth(const std::vector<std::string>& arguments);
    int registry(const std::vector<std::string>& arguments);
        int help();
        int version();
        
    
    };
}