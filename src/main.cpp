#include <iostream>
#include "CLI.hpp"
#include <vector>
#include <string>
#include "hypershell.hpp"
#include <tuple>

std::tuple<HyperShellConfig, std::vector<std::string>>
parse_jobs_from_cli(int argc, char* argv[]) {
    HyperShellConfig cfg;
    std::vector<std::string> jobs;

    CLI::App app("HyperShell CLI");

    app.add_flag("-v,--verbose", cfg.verbose, "Verbose mode");
    app.add_flag("-d,--dry-run", cfg.dry_run, "Dry run before executing");
    app.add_flag("-j,--json", cfg.json_output, "Output JSON");
    app.set_version_flag("-V,--version", "HyperShell v0.1.0");

    std::string mode_str = "local";
    app.add_option("--mode", mode_str, "Execution mode: local or remote")
       ->check(CLI::IsMember({"local", "remote"}));


    app.add_option("commands", jobs, "Commands to execute")->expected(0, -1);

    if (argc == 1) {
        std::cout << app.help() << std::endl;
        std::exit(0);
    }

    app.parse(argc, argv);

    if (mode_str == "remote") cfg.machine_location = Machine::REMOTE;
    else cfg.machine_location = Machine::LOCAL;


    return {cfg, jobs};
}


int main(int argc, char* argv[]) {
    auto [cfg, commands] = parse_jobs_from_cli(argc, argv);

    HyperShell app(cfg);

    std::cout << "verbose=" << cfg.verbose << "\n";
    std::cout << "dry_run=" << cfg.dry_run << "\n";
    std::cout << "json=" << cfg.json_output << "\n";
    std::cout << "mode=" << (cfg.machine_location == Machine::REMOTE ? "remote" : "local") << "\n";

    for (const auto& cmd : commands) {
        std::cout << "CMD: " << cmd << "\n";
    }

    // later: app.run(commands);
}
