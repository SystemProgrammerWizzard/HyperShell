#include <gtest/gtest.h>
#include "ssh.hpp"

TEST(SSH, MissingAllParameters)
{
  // Try creating an SSH object with invalid (empty) parameters.
  ssh_session ssh_connection = ssh_new();
  try
  {
    SSH sshOpt("", "", "", ssh_connection);
    FAIL() << "Expected std::invalid_argument exception";
  }
  catch (const std::invalid_argument &e)
  {
    EXPECT_EQ(std::string(e.what()), "Error: SSH parameters cannot be empty.");
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument exception";
  }
}

TEST(SSH, MissingConnection)
{
  // Try creating an SSH object with a null connection.
  ssh_session ssh_connection = ssh_new();
  try
  {
    SSH sshOpt("dave", "", "Oces2023", ssh_connection);
    FAIL() << "Expected std::invalid_argument exception";
  }
  catch (const std::invalid_argument &e)
  {
    EXPECT_EQ(std::string(e.what()), "Error: SSH parameters cannot be empty.");
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument exception";
  }
  ssh_free(ssh_connection);
}
TEST(SSH, MissingConnector)
{
  // Try creating an SSH object with a null connection.
  ssh_session ssh_connection = nullptr;
  try
  {
    SSH sshOpt("dave", "192.168.0.5", "Oces2023", ssh_connection);
    FAIL() << "Expected std::invalid_argument exception";
  }
  catch (const std::invalid_argument &e)
  {
    EXPECT_EQ(std::string(e.what()), "Error: SSH connection cannot be null.");
  }
  catch (...)
  {
    FAIL() << "Expected std::invalid_argument exception";
  }
  ssh_free(ssh_connection);
}

TEST(SSH, CreateValid)
{
  // Create an SSH object with valid parameters.
  ssh_session ssh_connection = ssh_new();
  SSH sshOpt("dave", "192.168.0.248", "Oces2023", ssh_connection);

  // Placeholder assertion until connection logic is implemented.
  SUCCEED() << "SSH object created successfully.";

  sshOpt.disconnect();
}

TEST(SSH, DestroyComplete)
{
  ssh_session ssh_connection = ssh_new();
  SSH sshOpt("dave", "192.168.0.248", "Oces2023", ssh_connection);
  sshOpt.disconnect();

// Check if it completely destroy
#ifdef UNIT_TEST
  EXPECT_TRUE(sshOpt.is_closed());
#endif
}

TEST(SSH, ValidSSH)
{
  // Create an SSH object with valid parameters.
  ssh_session ssh_connection = ssh_new();
  SSH sshOpt("dave", "192.168.0.248", "Oces2023", ssh_connection);
  bool success = sshOpt.connect();
  EXPECT_TRUE(success);
  sshOpt.disconnect();
}

TEST(SSH, InvalidSSH)
{
  // Create an SSH object with invalid parameters.
  ssh_session ssh_connection = ssh_new();
  SSH sshOpt("dave", "192.168.0.0", "Oces2023", ssh_connection);
  try
  {
    sshOpt.connect();
    FAIL() << "Expected std::runtime_error exception";
  }
  catch (const std::runtime_error &e)
  {
    EXPECT_EQ(std::string(e.what()), "Error connecting to 192.168.0.0: Socket error: No route to host");
  }
  catch (...)
  {
    FAIL() << "Expected std::runtime_error exception";
  }
  sshOpt.disconnect();
}