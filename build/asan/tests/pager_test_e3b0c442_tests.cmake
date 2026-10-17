add_test([=[PagerTest.AllocateAndReadWrite<betree::MemPager>]=]  /Users/vishwesh/Desktop/CascadeFrond/build/asan/tests/pager_test [==[--gtest_filter=PagerTest/0.AllocateAndReadWrite]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PagerTest.AllocateAndReadWrite<betree::MemPager>]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/vishwesh/Desktop/CascadeFrond/tests/pager_test.cpp:40]==]
    WORKING_DIRECTORY [==[/Users/vishwesh/Desktop/CascadeFrond/build/asan/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PagerTest.AllocateAndReadWrite<betree::FilePager>]=]  /Users/vishwesh/Desktop/CascadeFrond/build/asan/tests/pager_test [==[--gtest_filter=PagerTest/1.AllocateAndReadWrite]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PagerTest.AllocateAndReadWrite<betree::FilePager>]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/vishwesh/Desktop/CascadeFrond/tests/pager_test.cpp:40]==]
    WORKING_DIRECTORY [==[/Users/vishwesh/Desktop/CascadeFrond/build/asan/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(pager_test_TESTS [==[PagerTest.AllocateAndReadWrite<betree::MemPager>]==] [==[PagerTest.AllocateAndReadWrite<betree::FilePager>]==])
