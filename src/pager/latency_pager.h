#pragma once

#include "pager.h"
#include <memory>
#include <chrono>

namespace betree {

class LatencyPager : public Pager {
public:
    explicit LatencyPager(std::unique_ptr<Pager> inner_pager);
    ~LatencyPager() override = default;

    PageBuffer allocate_buffer() override;
    bool read_page(PageId page_id, PageBuffer& buffer) override;
    bool write_page(PageId page_id, const PageBuffer& buffer) override;
    PageId allocate_page_id() override;
    void free_page_id(PageId page_id) override;
    void sync() override;
    uint64_t page_count() const override;

    //time duration
    //total microseconds spent in I/O
    uint64_t get_total_read_time_us() const { return total_read_time_us_; }
    uint64_t get_total_write_time_us() const { return total_write_time_us_; }

private:
    std::unique_ptr<Pager> inner_;
    uint64_t total_read_time_us_{0};
    uint64_t total_write_time_us_{0};
};

} // namespace betree