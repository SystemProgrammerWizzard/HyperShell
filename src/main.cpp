#include <iostream>
#include "utils/command_line_options.hpp"

int main(int argc, char* argv[]) {
    CommandLineOptions cli;
    int status = cli.parse(argc, argv);
    if (status < 0) return 1;  // usage error
    if (status == 0 && (cli.opts().help || cli.opts().version)) return 0; // already printed & done

    // Normal run:
    if (cli.opts().verbose) {
        std::cout << "Executing with verbose mode\n";
    } else {
        std::cout << "Run without verbose mode\n";
        for (const auto& element: cli.cmd()){
            std::cout << element << std::endl;
        }
    }

    // Use cli.cmds() as your commands
    return 0;
}