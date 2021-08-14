#pragma once
#include <stdint.h>
#include "../IO/ports.h"
#include "../Memory/memory.h"
#include "pci.h"

#define ATA_MASTER 0x1F0
#define ATA_SLAVE  0x170

#define ATA_READ_SECTORS_COMMAND 0x20

#define ATA_BUFFER 0x1090 //512 bytes

char* ATAReadLBA(uint32_t lba, void* buffer);
int ATADetect();