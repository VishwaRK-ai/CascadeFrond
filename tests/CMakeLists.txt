# Smoke Test
add_executable(smoke_test smoke_test.cpp)
target_link_libraries(smoke_test gtest_main)
include(GoogleTest)
gtest_discover_tests(smoke_test)

# Pager Test
add_executable(pager_test pager_test.cpp)
target_link_libraries(pager_test gtest_main betree_pager)
gtest_discover_tests(pager_test)