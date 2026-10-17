#pragma once

#include "pager.h"
#include <vector>
#include <cstring> // for std::memcpy

namespace betree {

class MemPager : public Pager {
public:
    MemPager() = default;
    ~MemPager() override = default;

    //override from Pager interface
    PageBuffer allocate_buffer() override;
    bool read_page(PageId page_id, PageBuffer& buffer) override;
    bool write_page(PageId page_id, const PageBuffer& buffer) override;
    PageId allocate_page_id() override;
    void free_page_id(PageId page_id) override;
    void sync() override;
    uint64_t page_count() const override;

private:
    //store the actual page data in memory. 
    //the index in the vector -> corr to PageId.
    std::vector<PageBuffer> pages_;
    
    //Stack of page IDs that were freed and can be reused.
    std::vector<PageId> free_list_;
    
    //Track the total number of valid (allocated) pages.
    uint64_t active_page_count_ = 0;
};

} // namespace betree