add_test([=[SmokeTest.CompilationAndLinking]=]  /Users/vishwesh/Desktop/CascadeFrond/build/asan/tests/smoke_test [==[--gtest_filter=SmokeTest.CompilationAndLinking]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SmokeTest.CompilationAndLinking]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/vishwesh/Desktop/CascadeFrond/tests/smoke_test.cpp:3]==]
    WORKING_DIRECTORY [==[/Users/vishwesh/Desktop/CascadeFrond/build/asan/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(smoke_test_TESTS [==[SmokeTest.CompilationAndLinking]==])
