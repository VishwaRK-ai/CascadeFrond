#include "latency_pager.h"

namespace betree {

LatencyPager::LatencyPager(std::unique_ptr<Pager> inner_pager)
    : inner_(std::move(inner_pager)) {}

PageBuffer LatencyPager::allocate_buffer() { return inner_->allocate_buffer(); }
PageId LatencyPager::allocate_page_id() { return inner_->allocate_page_id(); }
void LatencyPager::free_page_id(PageId page_id) { inner_->free_page_id(page_id); }
void LatencyPager::sync() { inner_->sync(); }
uint64_t LatencyPager::page_count() const { return inner_->page_count(); }

bool LatencyPager::read_page(PageId page_id, PageBuffer& buffer) {
    auto start = std::chrono::steady_clock::now();
    bool result = inner_->read_page(page_id, buffer);
    auto end = std::chrono::steady_clock::now();
    total_read_time_us_ += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return result;
}

bool LatencyPager::write_page(PageId page_id, const PageBuffer& buffer) {
    auto start = std::chrono::steady_clock::now();
    bool result = inner_->write_page(page_id, buffer);
    auto end = std::chrono::steady_clock::now();
    total_write_time_us_ += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return result;
}

} // namespace betree