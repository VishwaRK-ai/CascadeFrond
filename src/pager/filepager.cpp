#include "filepager.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cerrno>
#include <stdexcept>

namespace betree {

FilePager::FilePager(const std::string& filename) {
#ifdef __APPLE__
    fd_ = open(filename.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd_ != -1) {
        fcntl(fd_, F_NOCACHE, 1);
    }
#else
    fd_ = open(filename.c_str(), O_RDWR | O_CREAT | O_DIRECT, 0666);
#endif
    if (fd_ == -1) {
        throw std::runtime_error("Failed to open database file");
    }
    
    struct stat st;
    if (fstat(fd_, &st) == 0) {
        active_page_count_ = st.st_size / PAGE_SIZE;
    }
}

FilePager::~FilePager() {
    if (fd_ != -1) {
        close(fd_);
    }
}

PageBuffer FilePager::allocate_buffer() {
    void* ptr = nullptr;
    if (posix_memalign(&ptr, PAGE_SIZE, PAGE_SIZE) != 0) return nullptr;
    return PageBuffer(static_cast<uint8_t*>(ptr));
}

PageId FilePager::allocate_page_id() {
    if (!free_list_.empty()) {
        PageId id = free_list_.back();
        free_list_.pop_back();
        active_page_count_++;
        return id;
    }
    return active_page_count_++;
}

void FilePager::free_page_id(PageId page_id) {
    free_list_.push_back(page_id);
    active_page_count_--;
}

bool FilePager::read_page(PageId page_id, PageBuffer& buffer) {
    off_t offset = page_id * PAGE_SIZE;
    size_t bytes_read = 0;
    uint8_t* ptr = buffer.get();

    while (bytes_read < PAGE_SIZE) {
        ssize_t res = pread(fd_, ptr + bytes_read, PAGE_SIZE - bytes_read, offset + bytes_read);
        if (res > 0) {
            bytes_read += res;
        } else if (res == 0) {
            return false; // EOF
        } else if (errno != EINTR) {
            return false; // Error
        }
    }
    return true;
}

bool FilePager::write_page(PageId page_id, const PageBuffer& buffer) {
    off_t offset = page_id * PAGE_SIZE;
    size_t bytes_written = 0;
    const uint8_t* ptr = buffer.get();

    while (bytes_written < PAGE_SIZE) {
        ssize_t res = pwrite(fd_, ptr + bytes_written, PAGE_SIZE - bytes_written, offset + bytes_written);
        if (res > 0) {
            bytes_written += res;
        } else if (errno != EINTR) {
            return false; // Error
        }
    }
    return true;
}

void FilePager::sync() {
#ifdef __APPLE__
    fcntl(fd_, F_FULLFSYNC);
#else
    fdatasync(fd_);
#endif
}

uint64_t FilePager::page_count() const {
    return active_page_count_;
}

} // namespace betree