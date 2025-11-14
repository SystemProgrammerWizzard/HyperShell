#include "ssh.hpp"

SSH::SSH(const std::string &username, const std::string &ip_address, const std::string &password)
{
    if (username.empty() || ip_address.empty() || password.empty())
    {
        throw std::invalid_argument("Error: SSH parameters cannot be empty.");
    }

    this->username = username;
    this->ip_address = ip_address;
    this->password = password;
    this->closed = false;

    ssh_connection = ssh_new();
    if (ssh_connection == nullptr)
    {
        throw std::runtime_error("Failed to allocate SSH session");
    }
}

SSH::SSH(SSH&& other) noexcept
        : username(std::move(other.username))
        , ip_address(std::move(other.ip_address))
        , password(std::move(other.password))
        , ssh_connection(other.ssh_connection)
        , closed(other.closed)
    {
        other.ssh_connection = nullptr;
        other.closed = true;
    }

SSH& SSH::operator=(SSH&& other) noexcept {
        if (this != &other) {
            if (ssh_connection != nullptr) {
                if (!closed) {
                    ssh_disconnect(ssh_connection);
                }
                ssh_free(ssh_connection);
            }
            
            username = std::move(other.username);
            ip_address = std::move(other.ip_address);
            password = std::move(other.password);
            ssh_connection = other.ssh_connection;
            closed = other.closed;
            
            // Nullify other
            other.ssh_connection = nullptr;
            other.closed = true;
        }
        return *this;
    }

bool SSH::connect()
{
    unsigned int port = 22;

    if (ssh_options_set(ssh_connection, SSH_OPTIONS_HOST, ip_address.c_str()) != SSH_OK)
        throw std::runtime_error(std::string("SSH host set error: ") + ssh_get_error(ssh_connection));

    if (ssh_options_set(ssh_connection, SSH_OPTIONS_USER, username.c_str()) != SSH_OK)
        throw std::runtime_error(std::string("SSH user set error: ") + ssh_get_error(ssh_connection));

    if (ssh_options_set(ssh_connection, SSH_OPTIONS_PORT, &port) != SSH_OK)
        throw std::runtime_error(std::string("SSH port set error: ") + ssh_get_error(ssh_connection));

    if (ssh_connect(ssh_connection) != SSH_OK)
        throw std::runtime_error(std::string("SSH connect error: ") + ssh_get_error(ssh_connection));

    if (ssh_userauth_password(ssh_connection, nullptr, password.c_str()) != SSH_AUTH_SUCCESS)
        throw std::runtime_error(std::string("SSH auth error: ") + ssh_get_error(ssh_connection));

    return true;
}

bool SSH::exec(std::string command)
{
    int rc;
    ssh_channel channel = ssh_channel_new(ssh_connection);
    if (channel == nullptr)
        throw std::runtime_error("Failed to create SSH channel");

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
        throw std::runtime_error(std::string("Failed to open channel: ") + ssh_get_error(ssh_connection));

    rc = ssh_channel_request_exec(channel, command.c_str());
    if (rc != SSH_OK)
        throw std::runtime_error(std::string("Failed to execute command: ") + ssh_get_error(ssh_connection));

    char buffer[256];
    int nbytes = ssh_channel_read(channel, buffer, sizeof(buffer) - 1, 0);
    if (nbytes > 0)
    {
        buffer[nbytes] = '\0';
        printf("%s", buffer);
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    return true;
}

SSH::~SSH()
{
    if (ssh_connection != nullptr)
    {
        if (!closed)
        {
            ssh_disconnect(ssh_connection);
        }
        ssh_free(ssh_connection);
        ssh_connection = nullptr;
    }
}

void SSH::disconnect()
{
    closed = true;
}