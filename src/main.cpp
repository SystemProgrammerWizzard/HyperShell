#include <iostream>
#include "CLI.hpp"
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    CLI::App app{"HyperShell CLI"};

    bool verbose = false;
    std::vector<std::string> commands;
    app.add_flag("-v,--verbose", verbose, "Verbose mode");
    app.set_version_flag("-V,--version", "HyperShell v0.1.0");

    app.add_option("commands", commands, "Commands to execute")->expected(0, -1);

    if (argc == 1) {
        std::cout << app.help() << std::endl;
        return 0;
    }

    CLI11_PARSE(app, argc, argv);
  

    if (verbose){
        std::cout << "[Verbose] Parsed" << commands.size() << "command(s)" << std::endl;
    }
    for (size_t i = 0; i < commands.size(); i++){
        std::cout << "Command #" << i+1 << commands[i] << std::endl; 
    }

    
    return 0;
}