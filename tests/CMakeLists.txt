cmake_minimum_required(VERSION 3.14)
project(CascadeFrondProject CXX)

# Set C++ standard to C++14 as you requested in your clang++ command
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(smoke_test smoke_test.cpp)
target_link_libraries(smoke_test gtest_main)
include(GoogleTest)
gtest_discover_tests(smoke_test)