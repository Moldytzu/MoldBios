#include "pci.h"

uint16_t PCIReadWord (uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
    outd(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));

    return (uint16_t)((ind(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
}

PCIChipset PCIGetChipset() {
    PCIChipset chipset;

    chipset.Vendor = PCIReadWord(0,0,0,PCI_CFG_VENDOR);
    chipset.Device = PCIReadWord(0,0,0,PCI_CFG_DEVICE);

    return chipset;
}