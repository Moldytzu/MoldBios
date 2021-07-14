#pragma once
#include <stdint.h>
#include <stddef.h>
#include "serial.h"
#include "../Misc/endianness.h"
#include "../IO/ports.h"
#include "../Misc/cstring.h"

#define FWCFG_DMA_PORT 0x518
#define FWCFG_ROOT 0x19

#define FWCFGCommand_ERROR (1 << 0)
#define FWCFGCommand_READ (1 << 1)
#define FWCFGCommand_SKIP (1 << 2)
#define FWCFGCommand_SELECT (1 << 3)
#define FWCFGCommand_WRITE (1 << 4)

struct FWCFGFile {
    uint32_t size;
    uint16_t selector;
    uint16_t reserved;
    char name[56];
} __attribute__((packed));

struct FWCFGCommand {
    uint32_t control;
    uint32_t length;
    uint64_t address;
} __attribute__((packed));

void RAMFBInit(int width, int height, int bpp);
