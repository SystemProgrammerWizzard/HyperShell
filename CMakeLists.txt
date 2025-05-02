cmake_minimum_required(VERSION 3.20)
project(HyperShell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libssh
find_library(LIBSSH_LIBRARY NAMES ssh REQUIRED)
include_directories(/usr/include/libssh) # or use target_include_directories

# Add source files to a library
add_library(hypershell_lib
    src/ssh.cpp
    src/terminal.cpp
    src/thread.cpp
)

target_include_directories(hypershell_lib PUBLIC include)
target_link_libraries(hypershell_lib PRIVATE ${LIBSSH_LIBRARY})

# Enable testing
include(CTest)
enable_testing()

# Fetch and make available GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Add test folder
add_subdirectory(tests)