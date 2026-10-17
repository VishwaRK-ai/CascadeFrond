#include "mempager.h"

namespace betree {

PageBuffer MemPager::allocate_buffer() {
    void* ptr = nullptr;
    if (posix_memalign(&ptr, PAGE_SIZE, PAGE_SIZE) != 0) {
        return nullptr;
    }
    return PageBuffer(static_cast<uint8_t*>(ptr));
}

PageId MemPager::allocate_page_id() {
    if (!free_list_.empty()) {
        PageId id = free_list_.back();
        free_list_.pop_back();
        active_page_count_++;
        return id;
    }
    pages_.push_back(allocate_buffer());
    active_page_count_++;
    return pages_.size() - 1;
}

void MemPager::free_page_id(PageId page_id) {
    if (page_id < pages_.size()) {
        free_list_.push_back(page_id);
        active_page_count_--;
    }
}

bool MemPager::read_page(PageId page_id, PageBuffer& buffer) {
    if (page_id >= pages_.size() || !pages_[page_id]) return false;
    std::memcpy(buffer.get(), pages_[page_id].get(), PAGE_SIZE);
    return true;
}

bool MemPager::write_page(PageId page_id, const PageBuffer& buffer) {
    if (page_id >= pages_.size()) return false;
    if (!pages_[page_id]) {
        pages_[page_id] = allocate_buffer();
    }
    std::memcpy(pages_[page_id].get(), buffer.get(), PAGE_SIZE);
    return true;
}

void MemPager::sync() {
    // No-op for memory pager
}

uint64_t MemPager::page_count() const {
    return active_page_count_;
}

} // namespace betree