#pragma once
#include <stdint.h>

static struct MoldBootDescriptor* globalMBDesc;

static void SerialPutStr(char* str) {
    for(int i = 0;str[i] != 0;i++)
        asm volatile("out %0, %1" :: "a"(str[i]), "Nd"(0x3F8));
}

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

static void* MBGetFunctionByType(uint8_t type) {
    for(int i = 0;i<globalMBDesc->numEntries;i++){
        if(globalMBDesc->entries[i].Type == type){
            return globalMBDesc->entries[i].Address;
        }
    }
    return 0;
}

static void PutStr(char* string) {
    if(MBGetFunctionByType(MB_T_PUTSTR) != 0)
        ((void (*)(char*))MBGetFunctionByType(MB_T_PUTSTR))(string);
}