#pragma once
#include <stdint.h>

static void* Addresses[32];

#define MB_T_PUTSTR 0
#define MB_T_PUTSTRS 1

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

static void MBPopulateAdresses(struct MoldBootDescriptor* globalMBDesc) {
    for(int i = 0;i<globalMBDesc->numEntries;i++){
        Addresses[globalMBDesc->entries[i].Type]=globalMBDesc->entries[i].Address;
    }
}

static void PutStr(char* string) {
    if(Addresses[MB_T_PUTSTR] != 0)
        ((void (*)(char*))Addresses[MB_T_PUTSTR])(string);
}

static void PutStrS(char* string) {
    if(Addresses[MB_T_PUTSTRS] != 0)
        ((void (*)(char*))Addresses[MB_T_PUTSTRS])(string);
}