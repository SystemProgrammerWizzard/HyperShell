#include <iostream>
#include "CLI.hpp"

int main(int argc, char* argv[]) {
    CLI::App app{"HyperShell CLI"};

    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose mode");
    app.set_version_flag("-V,--version", "HyperShell v0.1.0");

    CLI11_PARSE(app,argc, argv);

    if (verbose) std::cout << "Verbose mode enables\n";

    // Use cli.cmds() as your commands
    return 0;
}