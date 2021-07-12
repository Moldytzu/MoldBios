#pragma once
#include <stdint.h>
#include "../IO/ports.h"
#include "endianness.h"

#define FWCFG_SELECTOR_PORT 0x510 //w, 16-bit
#define FWCFG_DATA_PORT 0x511 //rw, ignored since QEMU 2.4, 8-bit
#define FWCFG_DMA_PORT 0x514

#define CONTROL_ERROR  (1 << 0)
#define CONTROL_READ   (1 << 1)
#define CONTROL_SKIP   (1 << 2)
#define CONTROL_SELECT (1 << 3)
#define CONTROL_WRITE  (1 << 4)

struct FWCFG_DMA {
    uint32_t Control;
    uint32_t Length;
    uint64_t Address;
} __attribute__((__packed__));

struct FWCFG_FILE {
    uint32_t Size;
    uint16_t Select;
    uint16_t Reserved;
    char Name[56];
} __attribute__((__packed__));

struct FWCFG_FILE_DIR {
    uint32_t Count;
    char FWCFG_FILE[56];
} __attribute__((__packed__)); //https://github.com/qemu/qemu/blob/master/docs/specs/fw_cfg.txt

void FWCFGDMATransfer(void* buffer, uint32_t len, uint32_t control);
int FWCFGLocateFile(const char* file);