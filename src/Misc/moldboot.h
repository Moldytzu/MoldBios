#pragma once
#include <stdint.h>

#define MB_T_PUTSTR 0

struct __attribute__((packed)) MoldBootEntry {
    void* Address;
    uint8_t Type;
};

struct __attribute__((packed)) MoldBootHardware {
    void* MemoryMapAddress;

    void* FramebufferAddress;
    void* FramebufferWidth;
    void* FramebufferHeight;
};

struct __attribute__((packed)) MoldBootDescriptor {
    uint8_t signature[2]; //Always MB
    uint8_t numEntries;
    struct MoldBootHardware hw;
    struct MoldBootEntry entries[32];
};