#ifndef HYPERSHELL_HPP
#define HYPERSHELL_HPP

#include <string>
#include <queue>
#include "ssh.hpp"
#include <optional>

typedef enum Machine {
    REMOTE,
    LOCAL
}Machine;

typedef struct HyperShellConfig {
    bool verbose = false;
    bool dry_run = false;
    bool json_output = false;
    int max_parallel = 1;
    Machine machine_location = Machine::LOCAL;
    std::optional<SSH> machine;

} HyperShellConfig;

class HyperShell{
private:
    HyperShellConfig config;
    void run_job(const std::string command);
    void run_remote(const std::string user, const std::string password);
public:
    explicit HyperShell(HyperShellConfig cfg);
    void run(const std::vector<std::string> job);
};

#endif // HYPERSHELL.HPP