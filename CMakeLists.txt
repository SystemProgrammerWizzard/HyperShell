# ============================================================================
# HyperShell - A C++ SSH Terminal Application
# ============================================================================
cmake_minimum_required(VERSION 3.20)
project(HyperShell VERSION 1.0.0 LANGUAGES CXX)

# ============================================================================
# Compiler Settings
# ============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================
# Find Dependencies
# ============================================================================
# Find libssh (modern way using PkgConfig if available)
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(LIBSSH REQUIRED libssh)
else()
    find_library(LIBSSH_LIBRARIES NAMES ssh REQUIRED)
    find_path(LIBSSH_INCLUDE_DIRS libssh/libssh.h REQUIRED)
endif()

# ============================================================================
# Main Library
# ============================================================================
add_library(hypershell_lib
    src/utils/command_line_options.cpp
    src/ssh.cpp
    src/terminal.cpp
    src/task.cpp
)

target_include_directories(hypershell_lib 
    PUBLIC include
    PRIVATE ${LIBSSH_INCLUDE_DIRS}
)

target_link_libraries(hypershell_lib 
    PRIVATE ${LIBSSH_LIBRARIES}
)

# ============================================================================
# Main Executable
# ============================================================================
add_executable(hypershell src/main.cpp)
target_link_libraries(hypershell PRIVATE hypershell_lib)

# ============================================================================
# Testing Setup
# ============================================================================
option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    
    # Fetch GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)
    
    add_subdirectory(tests)
endif()