cmake_minimum_required(VERSION 3.20)
project(betree_dbms CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Fetch GoogleTest FIRST (without our strict warnings)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# 2. NOW turn on strict warnings so they only apply to our code
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Link the source directory
add_subdirectory(src)

# Allow tests to be discovered
enable_testing()
add_subdirectory(tests)