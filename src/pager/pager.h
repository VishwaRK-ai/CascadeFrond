#pragma once

#include <cstdint>
#include <memory>
#include <cstdlib>

namespace betree {

//page size
constexpr size_t PAGE_SIZE = 4096;

//idk
using PageId = uint64_t;
constexpr PageId INVALID_PAGE_ID = ~PageId{0};

//custom delete for memory allocated via posix_memalign/aligned_alloc
struct AlignedDeleter {
    void operator()(uint8_t* ptr) const {
        std::free(ptr);
    }
};

//pointer representing an aligned 4kb page buffer that the caller owns ig
using PageBuffer = std::unique_ptr<uint8_t[], AlignedDeleter>;

/*. Abbstract interface for disk access. */
class Pager {
public:
    virtual ~Pager() = default;

    //allocate an aligned memory buffer
    virtual PageBuffer allocate_buffer() = 0;

    //read a page from the backing store into the provided buffer
    virtual bool read_page(PageId page_id, PageBuffer& buffer) = 0;// to apass ptr for i/o par
    
    //write a page from the buffer into the backing store
    virtual bool write_page(PageId page_id, const PageBuffer& buffer) = 0;

    //allocate a new logical page id (pull from free list or extend file)for now free list
    virtual PageId allocate_page_id() = 0;

    //free a logical page ID (push to free list)
    virtual void free_page_id(PageId page_id) = 0;

    //flush dirty pages to stable storage (fsync/fdatasync)
    virtual void sync() = 0;

    //return the total number of managed pages
    virtual uint64_t page_count() const = 0;
};

} // namespace betree