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

    CLI::App app("HyperShell CLI", "hypershell");
    app.require_subcommand(1);
    app.set_version_flag("-V,--version", "HyperShell v0.1.0");

    auto* ssh_cmd = app.add_subcommand("ssh", "Execute commands on remote hosts via SSH");
    std::string user;
    std::string hosts;
    std::string password;
    ssh_cmd->add_option("--user", user, "SSH username")->required();
    ssh_cmd->add_option("--password", password, "SSH password")->required();
    ssh_cmd->add_option("--hosts", hosts, "Comma-separated list of hosts")->required();
    ssh_cmd->add_option("--cmd", jobs, "Commands to execute")->required();
    ssh_cmd->add_flag("-v,--verbose", cfg.verbose, "Verbose mode");
    ssh_cmd->add_flag("-d,--dry-run", cfg.dry_run, "Dry run before executing");
    ssh_cmd->add_flag("-j,--json", cfg.json_output, "Output JSON");

    auto* local_cmd = app.add_subcommand("local", "Execute commands locally");
    local_cmd->add_option("--cmd", jobs, "Commands to execute")->required();
    local_cmd->add_flag("-v,--verbose", cfg.verbose, "Verbose mode");
    local_cmd->add_flag("-d,--dry-run", cfg.dry_run, "Dry run before executing");
    local_cmd->add_flag("-j,--json", cfg.json_output, "Output JSON");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::exit(app.exit(e));
    }

    if (ssh_cmd->parsed()) {
        cfg.machine_location = Machine::REMOTE;

        cfg.machine.emplace(user, hosts, password);
        
    } else if (local_cmd->parsed()) {
        cfg.machine_location = Machine::LOCAL;
    }

    return {std::move(cfg), std::move(jobs)};
}

int main(int argc, char* argv[]) {
    auto [cfg, commands] = parse_jobs_from_cli(argc, argv);

    HyperShell app(std::move(cfg));

    std::cout << "verbose=" << cfg.verbose << "\n";
    std::cout << "dry_run=" << cfg.dry_run << "\n";
    std::cout << "json=" << cfg.json_output << "\n";
    std::cout << "mode=" << (cfg.machine_location == Machine::REMOTE ? "remote" : "local") << "\n";

    for (const auto& cmd : commands) {
        std::cout << "CMD: " << cmd << "\n";
    }

    // later: app.run(commands);
}