cmake_minimum_required(VERSION 3.20)
project(betree_dbms CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Strict warnings
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Allow tests to be discovered
enable_testing()
add_subdirectory(tests)

#bypassing mac errors
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  target_compile_options(gtest PRIVATE "-Wno-character-conversion")
endif()