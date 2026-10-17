#include "checksum.h"

namespace betree {

uint32_t calculate_page_checksum(PageId page_id, const uint8_t* buffer_data, size_t size) {
    uint32_t hash = 2166136261u; //FNV offset basis
    
    //hash the page ID first to catch misdirected writes
    const uint8_t* id_ptr = reinterpret_cast<const uint8_t*>(&page_id);
    for (size_t i = 0; i < sizeof(PageId); ++i) {
        hash ^= id_ptr[i];
        hash *= 16777619u; //FNV prime no
    }
    
    //hash the rest of the buffer payload
    for (size_t i = 0; i < size; ++i) {
        hash ^= buffer_data[i];
        hash *= 16777619u;
    }
    
    return hash;
}

} // namespace betree