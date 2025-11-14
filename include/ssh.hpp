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
public:
    ~SSH();
    SSH(const std::string &username, const std::string &ip_address, const std::string &password);
    SSH(const SSH&) = delete;
    SSH(SSH&& other) noexcept;
    SSH& operator=(SSH&& other) noexcept;
    SSH& operator=(const SSH&) = delete;
    bool connect();
    bool exec(std::string);
    void disconnect();
#ifdef UNIT_TESTING
    bool is_connected() const { return closed; }
#endif
};

#endif
