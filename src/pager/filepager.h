#pragma once

#include "pager.h"
#include <string>
#include <vector>

namespace betree {

class FilePager : public Pager {
public:
    // Opens or creates the file, enforcing O_DIRECT/F_NOCACHE
    explicit FilePager(const std::string& filename);
    
    // Closes the file descriptor
    ~FilePager() override;

    // Overrides from the Pager interface
    PageBuffer allocate_buffer() override;
    bool read_page(PageId page_id, PageBuffer& buffer) override;
    bool write_page(PageId page_id, const PageBuffer& buffer) override;
    PageId allocate_page_id() override;
    void free_page_id(PageId page_id) override;
    void sync() override;
    uint64_t page_count() const override;

private:
    int fd_ = -1; 
    uint64_t active_page_count_ = 0;
    
    // In-memory free list for reused pages. 
    //FOR NOW SAVE IN RAM, LATER INTO WAL IN PHASE 7
    std::vector<PageId> free_list_;
};

} // namespace betree