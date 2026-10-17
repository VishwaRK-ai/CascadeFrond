#include "counting_pager.h"

namespace betree{

CountingPager::CountingPager(std::unique_ptr<Pager> inner_pager)
    : inner_(std::move(inner_pager)) {}

PageBuffer CountingPager::allocate_buffer() { return inner_->allocate_buffer(); }

PageId CountingPager::allocate_page_id() { return inner_->allocate_page_id(); }

void CountingPager::free_page_id(PageId page_id) { inner_->free_page_id(page_id); }

void CountingPager::sync() { inner_->sync(); }
uint64_t CountingPager::page_count() const { return inner_->page_count(); }

bool CountingPager::read_page(PageId page_id, PageBuffer& buffer) {
    read_count_.fetch_add(1, std::memory_order_relaxed);
    return inner_->read_page(page_id, buffer);
}

bool CountingPager::write_page(PageId page_id, const PageBuffer& buffer) {
    write_count_.fetch_add(1, std::memory_order_relaxed);
    return inner_->write_page(page_id, buffer);
}

} // namespace betree