# Add individual test executables
add_executable(test_ssh test_ssh.cpp)
target_link_libraries(test_ssh gtest_main hypershell_lib)
target_include_directories(test_ssh PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME SSHTest COMMAND test_ssh)

add_executable(test_terminal test_terminal.cpp)
target_link_libraries(test_terminal gtest_main hypershell_lib)
target_include_directories(test_terminal PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME TerminalTest COMMAND test_terminal)

add_executable(test_thread test_thread.cpp)
target_link_libraries(test_thread gtest_main hypershell_lib)
target_include_directories(test_thread PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME ThreadTest COMMAND test_thread)