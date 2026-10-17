#include <gtest/gtest.h>
#include "../src/pager/mempager.h"
#include "../src/pager/filepager.h"
#include <cstring>

using namespace std;

namespace betree {

//def a factory so we can isntantiate the different pagers
template <typename T>
unique_ptr<Pager> create_pager();

template <>
unique_ptr<Pager> create_pager<MemPager>() {
    return make_unique<MemPager>();
}

template <>
unique_ptr<Pager> create_pager<FilePager>() {
    //creates a temporary file until testing
    return make_unique<FilePager>("test_backend.db");
}

template <typename T>
class PagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        pager = create_pager<T>();
    }
    void TearDown() override {
        //clean up the file if its a FilePager
        remove("test_backend.db"); 
    }
    unique_ptr<Pager> pager;
};

// The list of backend types we want to test
using PagerTypes = ::testing::Types<MemPager, FilePager>;
TYPED_TEST_SUITE(PagerTest, PagerTypes);

TYPED_TEST(PagerTest, AllocateAndReadWrite) {
    PageId id = this->pager->allocate_page_id();
    auto write_buf = this->pager->allocate_buffer();
    
    //Fill buffer with a known pattern
    memset(write_buf.get(), 0xAB, PAGE_SIZE);
    EXPECT_TRUE(this->pager->write_page(id, write_buf));

    auto read_buf = this->pager->allocate_buffer();
    EXPECT_TRUE(this->pager->read_page(id, read_buf));

    //Verify data was written and read correctly
    EXPECT_EQ(memcmp(write_buf.get(), read_buf.get(), PAGE_SIZE), 0);
}

} // namespace betree