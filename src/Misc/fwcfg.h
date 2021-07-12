#pragma once
#include <stdint.h>

#define FWCFG_SELECTOR_PORT 0x510 //w, 16-bit
#define FWCFG_DATA_PORT 0x511 //rw, ignored since QEMU 2.4, 8-bit
#define FWCFG_DMA_PORT 0x514 //

typedef struct FWCFG_DMA {
    uint32_t Control;
    uint32_t Length;
    uint64_t Address;
} __attribute__((__packed__));

typedef struct FWCFG_FILE {
    uint32_t Size;
    uint16_t Select;
    uint16_t Reserved;
    char Name[56];
} __attribute__((__packed__));

typedef struct FWCFG_FILE_DIR {
    uint32_t Count;
    char FWCFG_FILE[56];
} __attribute__((__packed__));