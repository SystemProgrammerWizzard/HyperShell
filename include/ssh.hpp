#ifndef SSH_H
#define SSH_H

#include <string>
#include <libssh/libssh.h>
#include <stdexcept>

class SSH
{
private:
    std::string username;
    std::string ip_address;
    std::string password;
    ssh_session ssh_connection;
    bool closed = false;
    // Private constructor: only the create method can call this.
public:
    // Public destructor so that std::optional can destroy SSH objects
    ~SSH();
    SSH(const std::string &username, const std::string &ip_address, const std::string &password);

    bool connect();
    bool exec(std::string);
    void disconnect();
#ifdef UNIT_TESTING
    bool is_connected() const { return closed; }
#endif
};

#endif