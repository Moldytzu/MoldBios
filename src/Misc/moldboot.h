#pragma once
#include <stdint.h>

#define MB_T_PUTSTR 0
#define MB_T_PUTSTRS 1

struct __attribute__((packed)) MoldBootHardware {
    void* MemoryMapAddress;

    void* FramebufferAddress;
    uint32_t FramebufferWidth;
    uint32_t FramebufferHeight;
};

struct __attribute__((packed)) MoldBootDescriptor {
    uint8_t signature[2]; //Always MB
    uint8_t numEntries;
    struct MoldBootHardware hardware;
    void* entries[32];
};