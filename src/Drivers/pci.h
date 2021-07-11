#pragma once
#include <stdint.h>
#include "../IO/ports.h"

#define PCI_CFG_ADDRESS 0xCF8
#define PCI_CFG_VENDOR 0x00
#define PCI_CFG_DEVICE 0x02

typedef struct {
    uint16_t Vendor;
    uint16_t Device;
} PCIChipset;

#define Q35_VENDOR 0x8086
#define Q35_DEVICE 0x29C0
#define I440FX_VENDOR 0x8086
#define I440FX_DEVICE 0x1237

uint16_t PCIReadWord(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
PCIChipset PCIGetChipset();