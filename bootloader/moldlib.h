#pragma once
#include <stdint.h>

static void SerialPutStr(char* str) {
    for(int i = 0;str[i] != 0;i++)
        asm volatile("out %0, %1" :: "a"(str[i]), "Nd"(0x3F8));
}

struct __attribute__((packed)) MoldBootEntry {
    void* Address;
    uint32_t Type;
};

struct __attribute__((packed)) MoldBootHardware {
    void* MemoryMapAddress;

    void* FramebufferAddress;
    void* FramebufferWidth;
    void* FramebufferHeight;
};

struct __attribute__((packed)) MoldBootDescriptor {
    uint8_t signature[2]; //Always MB
    uint32_t numEntries;
    struct MoldBootHardware hw;
    struct MoldBootEntry entries[32];
};