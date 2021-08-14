#pragma once
#include <stdint.h>

//IMPORTANT: change this if you change the variable name of the entry parameter
#define GlobalMB mbdesc

#define MB_F_PUTSTR   0
#define MB_F_PUTSTRS  1
#define MB_F_INTSTR   2
#define MB_F_DISKREAD 3
#define MB_F_SETCLR   4

#define WHITE   0xFFFFFF
#define BLACK   0x000000
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define YELLOW  0xFFF000
#define MAGENTA 0xFF00F0
#define CYAN    0x00FFF0
#define ORANGE  0xFFA500

#define PutStr(string) ((void (*)(char*))GlobalMB->entries[MB_F_PUTSTR])(string)
#define PutStrSerial(string) ((void (*)(char*))GlobalMB->entries[MB_F_PUTSTRS])(string)
#define PutPix(x,y,colour) *(uint32_t*)(x*4 + (GlobalMB->hardware.FrameBuffer.Width*y *4) + GlobalMB->hardware.FrameBuffer.Address) = colour;
#define inttostr(num) ((char* (*)())GlobalMB->entries[MB_F_INTSTR])(num)
#define ReadDisk(lba,buffer) ((uint8_t* (*)())GlobalMB->entries[MB_F_DISKREAD])(lba,buffer)
#define SetColor(color) ((void (*)(uint32_t))GlobalMB->entries[MB_F_SETCLR])(color)

struct __attribute__((packed)) MoldBootMemoryMap {
    uint32_t HardwareReservedStart;
    uint32_t HardwareReservedEnd;
    
    uint32_t FirmwareReservedStart;
    uint32_t FirmwareReservedEnd;

    uint32_t FreeStart;
    uint32_t FreeEnd;
};

struct __attribute__((packed)) MoldBootFrameBuffer {
    void* Address;
    uint32_t Width;
    uint32_t Height;
};

struct __attribute__((packed)) MoldBootHardware {
    struct MoldBootMemoryMap MemoryMap;
    struct MoldBootFrameBuffer FrameBuffer;
};

struct __attribute__((packed)) MoldBootDescriptor {
    uint8_t signature[2]; //Always MB
    uint8_t numEntries;
    struct MoldBootHardware hardware;
    void* entries[32];
};