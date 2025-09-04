#ifndef COMMAND_LINE_OPTIONS_HPP
#define COMMAND_LINE_OPTIONS_HPP
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

struct UserOptions {
    int verbose = 0;
    int help = 0;
    int version = 0;
    std::string output;
};

class CommandLineOptions {
    private:
        UserOptions userOptions;
        std::vector<std::string> command;
    public:
        
        const UserOptions& opts() const {return userOptions; };
        void display(std::ostream& os, const char* progname) const;
        int parse(int argc, char* argv[]);
        const std::vector<std::string>& cmd() const {return command;};
        
};

#endif // COMMAND_LINE_OPTIONS_HPP