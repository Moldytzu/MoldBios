#pragma once
#include <stdint.h>
#include <stddef.h>
#include "serial.h"
#include "../Misc/endianness.h"
#include "../IO/ports.h"
#include "../Misc/cstring.h"

#define FWCFG_DMA_PORT 0x518
#define FWCFG_ROOT 0x19

#define FWCFGCommand_ERROR  (1 << 0)
#define FWCFGCommand_READ   (1 << 1)
#define FWCFGCommand_SKIP   (1 << 2)
#define FWCFGCommand_SELECT (1 << 3)
#define FWCFGCommand_WRITE  (1 << 4)

#define VideoMemory 0x100000

#define CursorX *((uint32_t*)0x1000)
#define CursorY *((uint32_t*)0x1004)
#define ScreenW *((uint16_t*)0x1008)
#define ScreenH *((uint32_t*)0x100A)

struct FWCFGFile {
    uint32_t Size;
    uint16_t Selector;
    uint8_t Offset[2];
    char Name[56];
} __attribute__((packed));

struct FWCFGCommand {
    uint32_t Control;
    uint32_t Length;
    uint64_t Address;
} __attribute__((packed));

struct RAMFBStruct {
    uint64_t Address;
    uint32_t FOURCC;
    uint32_t Flags;
    uint32_t Width;
    uint32_t Height;
    uint32_t Stride;
} __attribute__((packed)) ;

void RAMFBInit(int width, int height);
void RAMFBPutPix(int x,int y, uint32_t clr);
void RAMFBPutRect(int x,int y, int w, int h, uint32_t clr);
void RAMFBPutRectF(int x,int y, int w, int h, uint32_t clr);
void RAMFBPutChar(int x, int y, char chr);
void RAMFBPutStr(char* str);
