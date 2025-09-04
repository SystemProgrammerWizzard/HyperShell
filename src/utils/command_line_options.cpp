#include "utils/command_line_options.hpp"

void CommandLineOptions::display(std::ostream& os, const char* progname) const {
    os << "Usage: " << progname << " [options] [commands...]\n"
       << "Options:\n"
       << "  -h            Show help message\n"
       << "  -V            Show version information\n"
       << "  -v            Verbose mode\n";
}

int CommandLineOptions::parse(int argc, char* argv[]) {
    if (argc == 1) {
        display(std::cout, argv[0]);
        return -1;
    }
    optind = 1;

    int opt;
    while ((opt = getopt(argc, argv, "vhV")) != -1) {
        switch (opt) {
            case 'v': userOptions.verbose = 1; break;
            case 'h':
                userOptions.help = 1;
                display(std::cout, argv[0]);
                return 0;      
            case 'V':
                userOptions.version = 1;
                std::puts("HyperShell version 0.1.0");
                return 0;
            default:
                display(std::cout, argv[0]);
                return -1;
        }
    }

    // Collect non-option args as commands
    for (int i = optind; i < argc; ++i) command.push_back(argv[i]);

    // If you REQUIRE at least one command:
    if (command.empty()) {
        display(std::cout, argv[0]);
        return -1;
    }

    return 0;
}

