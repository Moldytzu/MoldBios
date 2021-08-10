#pragma once
#include <stdint.h>

//IMPORTANT: change this if you change the variable name of the entry parameter
#define GlobalMB mbdesc

#define MB_F_PUTSTR 0
#define MB_F_PUTSTRS 1

#define PutStr(string) ((void (*)(char*))GlobalMB->entries[MB_F_PUTSTR])(string);
#define PutStrSerial(string) ((void (*)(char*))GlobalMB->entries[MB_F_PUTSTRS])(string);

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