#include "ssh.hpp"

SSH::SSH(const std::string &username, const std::string &ip_address, const std::string &password, ssh_session ssh_connection)
{
    if (username.empty() || ip_address.empty() || password.empty())
    {
        throw std::invalid_argument("Error: SSH parameters cannot be empty.");
    }
    if (ssh_connection == nullptr)
    {
        throw std::invalid_argument("Error: SSH connection cannot be null.");
    }

    this->username = username;
    this->ip_address = ip_address;
    this->password = password;
    this->ssh_connection = ssh_connection;
    this->closed = false;
}

bool SSH::connect()
{
    // Default SSH port
    unsigned int port = 22;

    // Set SSH options
    if (ssh_options_set(ssh_connection, SSH_OPTIONS_HOST, ip_address.c_str()) != SSH_OK)
    {
        fprintf(stderr, "Error setting SSH host: %s\n", ssh_get_error(ssh_connection));
        return false;
    }
    if (ssh_options_set(ssh_connection, SSH_OPTIONS_USER, username.c_str()) != SSH_OK)
    {
        fprintf(stderr, "Error setting SSH username: %s\n", ssh_get_error(ssh_connection));
        return false;
    }
    if (ssh_options_set(ssh_connection, SSH_OPTIONS_PORT, &port) != SSH_OK)
    {
        fprintf(stderr, "Error setting SSH port: %s\n", ssh_get_error(ssh_connection));
        return false;
    }

    // Establish the SSH connection
    int rc = ssh_connect(ssh_connection);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error connecting to %s: %s\n", ip_address.c_str(), ssh_get_error(ssh_connection));
        return false;
    }

    // Authenticate with password
    rc = ssh_userauth_password(ssh_connection, nullptr, password.c_str());
    if (rc != SSH_AUTH_SUCCESS)
    {
        fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(ssh_connection));

        return false;
    }

    return true;
}

SSH::~SSH()
{
    if (closed)
    {
        ssh_disconnect(ssh_connection);
        ssh_free(ssh_connection);
    }
}

void SSH::disconnect()
{
    closed = true;
}