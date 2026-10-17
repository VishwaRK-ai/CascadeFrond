cmake_minimum_required(VERSION 3.20)
project(betree_dbms CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest first, so the strict warnings below don't apply to its sources
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Strict warnings (only for our targets, defined after this line)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Allow tests to be discovered
enable_testing()
add_subdirectory(tests)