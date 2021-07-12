#pragma once
#include <stdint.h>

struct RAMFB {
    uint64_t Address;
    uint32_t FOURCC;
    uint32_t Flags;
    uint32_t Width;
    uint32_t Height;
    uint32_t Stride;
}__attribute__((packed));