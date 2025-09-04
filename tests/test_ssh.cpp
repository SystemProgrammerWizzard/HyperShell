#include <gtest/gtest.h>
#include "ssh.hpp"

TEST(SSH, MissingAllParameters)
{
  // Try creating an SSH object with invalid (empty) parameters.
  try
  {
    SSH sshOpt("", "", "");
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

TEST(SSH, MissingAddress)
{
  try
  {
    SSH sshOpt("dave", "", "Oces2023");
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

TEST(SSH, CreateValid)
{
  // Create an SSH object with valid parameters.
  SSH sshOpt("debian", "localhost", "debian");

  // Placeholder assertion until connection logic is implemented.
  SUCCEED() << "SSH object created successfully.";

  sshOpt.disconnect();
}

TEST(SSH, DestroyComplete)
{
  SSH sshOpt("debian", "localhost", "debian");
  sshOpt.disconnect();

// Check if it completely destroy
#ifdef UNIT_TEST
  EXPECT_TRUE(sshOpt.is_closed());
#endif
}

TEST(SSH, ValidSSH)
{
  // Create an SSH object with valid parameters.
  SSH sshOpt("debian", "localhost", "debian");
  bool success = sshOpt.connect();
  EXPECT_TRUE(success);
  sshOpt.disconnect();
}

TEST(SSH, InvalidSSH)
{
  // Create an SSH object with invalid parameters.
  SSH sshOpt("dave", "0.0.0.1", "Oces2023");
  bool success;
  try
  {
    success = sshOpt.connect();
    FAIL() << "Expected std::runtime_error exception";
  }
  catch (const std::runtime_error &e)
  {
    EXPECT_FALSE(success);
  }
  catch (...)
  {
    FAIL() << "Expected std::runtime_error exception";
  }
  sshOpt.disconnect();
}

TEST(SSH, Execute)
{

  SSH sshOpt("debian", "localhost", "debian");
  bool success = sshOpt.connect();
  sshOpt.exec("ls");
  EXPECT_TRUE(success);
  sshOpt.disconnect();
}
