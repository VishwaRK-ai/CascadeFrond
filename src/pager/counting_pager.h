#pragma once

#include "pager.h"
#include <memory>
#include <atomic>

namespace betree {

class CountingPager : public Pager {
public:
    //take ownership of the underlying pager (FilePager)
    explicit CountingPager(std::unique_ptr<Pager> inner_pager);
    ~CountingPager() override = default;

    PageBuffer allocate_buffer() override;
    bool read_page(PageId page_id, PageBuffer& buffer) override;
    bool write_page(PageId page_id, const PageBuffer& buffer) override;
    PageId allocate_page_id() override;
    void free_page_id(PageId page_id) override;
    void sync() override;
    uint64_t page_count() const override;

    //metric get-ers
    uint64_t get_read_count() const { return read_count_.load(); }
    uint64_t get_write_count() const { return write_count_.load(); }

private:
    std::unique_ptr<Pager> inner_;
    std::atomic<uint64_t> read_count_{0};
    std::atomic<uint64_t> write_count_{0};
};

} // namespace betree