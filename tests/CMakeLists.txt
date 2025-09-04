# ============================================================================
# Test Configuration
# ============================================================================

# List of all test files
set(TEST_SOURCES
    test_ssh.cpp
    test_terminal.cpp
    test_task.cpp
)

# Create tests for each source file
foreach(test_source ${TEST_SOURCES})
    # Get test name by removing extension
    get_filename_component(test_name ${test_source} NAME_WE)
    
    # Create executable
    add_executable(${test_name} ${test_source})
    
    # Link libraries
    target_link_libraries(${test_name} 
        PRIVATE 
        gtest_main 
        hypershell_lib
    )
    
    # Add to CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()