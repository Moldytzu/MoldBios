#pragma once
#include <stdint.h>

static void* Addresses[32];

#define MB_F_PUTSTR 0
#define MB_F_PUTSTRS 1


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
    void* entries[32];
};

static void MBPopulateAdresses(struct MoldBootDescriptor* globalMBDesc) {
    for(int i = 0;i<globalMBDesc->numEntries;i++){
        Addresses[i] = globalMBDesc->entries[i];
    }
}

static void PutStr(char* string) {
    if(Addresses[MB_F_PUTSTR] != 0)
        ((void (*)(char*))Addresses[MB_F_PUTSTR])(string);
}

static void PutStrS(char* string) {
    if(Addresses[MB_F_PUTSTRS] != 0)
        ((void (*)(char*))Addresses[MB_F_PUTSTRS])(string);
}