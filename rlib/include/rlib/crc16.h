#pragma once

#include <cstddef>
#include <cstdint>

namespace rlib {

uint16_t crc16_modbus(const void* data, size_t length, uint16_t last_chunk_crc = 0xFFFF);

}  // namespace rlib
