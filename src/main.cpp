#include "command.hpp"

int main(int argc, char* argv[])
{
    srcinit::Command command;
    return command.run(argc, argv);
}