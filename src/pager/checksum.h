#pragma once

#include "pager.h"
#include <cstdint>

namespace betree {

// Computes a checksum of the buffer, incorporating the page_id to prevent 
// misdirected write corruption.
// Ensure the byte layout of your page reserves the first 4 or 8 bytes 
// for the checksum itself, so this function should only hash the REST of the buffer.
uint32_t calculate_page_checksum(PageId page_id, const uint8_t* buffer_data, size_t size);

} // namespace betree