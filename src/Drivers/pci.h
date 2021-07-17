#pragma once
#include <stdint.h>
#include "../IO/ports.h"

#define PCI_CFG_ADDRESS 0xCF8
#define PCI_CFG_VENDOR 0x00
#define PCI_CFG_DEVICE 0x02
#define PCI_CFG_INTERFACE 0x09
#define PCI_CFG_SUBCLASS 0x0A
#define PCI_CFG_CLASS 0x0B

typedef struct {
    uint16_t Vendor;
    uint16_t Device;
} PCIChipset;

#define Q35_VENDOR 0x8086
#define Q35_DEVICE 0x29C0
#define I440FX_VENDOR 0x8086
#define I440FX_DEVICE 0x1237
#define MICROVM_VENDOR_DEVICE 0xFFFF

uint16_t PCIReadWord(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint8_t PCIFindDevice(uint8_t cls, uint8_t subcls, uint8_t programif);
PCIChipset PCIGetChipset();
