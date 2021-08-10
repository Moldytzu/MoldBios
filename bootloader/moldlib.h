#pragma once
#include <stdint.h>

//IMPORTANT: change this if you change the variable name of the entry parameter
#define GlobalMB mbdesc

#define MB_F_PUTSTR 0
#define MB_F_PUTSTRS 1

#define PutStr(string) ((void (*)(char*))GlobalMB->entries[MB_F_PUTSTR])(string);
#define PutStrSerial(string) ((void (*)(char*))GlobalMB->entries[MB_F_PUTSTRS])(string);
#define PutPix(x,y,colour) *(uint32_t*)(x*4 + (GlobalMB->hardware.FramebufferWidth*y *4) + GlobalMB->hardware.FramebufferAddress) = colour;

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