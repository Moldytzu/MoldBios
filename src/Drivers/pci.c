#include "pci.h"

uint16_t PCIReadWord (uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
    outd(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));

    return inw(0xCFC + (offset & 2));
}

uint16_t PCIReadByte (uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {
    outd(PCI_CFG_ADDRESS, (uint32_t)((bus << 16) | (slot << 11) | (function << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)));

    return inb(0xCFC + (offset & 3));
}

PCIChipset PCIGetChipset() {
    PCIChipset chipset;

    chipset.Vendor = PCIReadWord(0,0,0,PCI_CFG_VENDOR);
    chipset.Device = PCIReadWord(0,0,0,PCI_CFG_DEVICE);

    return chipset;
}

uint8_t PCIFindDevice(uint8_t cls, uint8_t subcls, uint8_t programif) {
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
       		for (int function = 0; function < 8; function++) {
       			 if(PCIReadByte(bus, slot, function, PCI_CFG_CLASS) == cls && PCIReadByte(bus, slot, function, PCI_CFG_SUBCLASS) == subcls && PCIReadByte(bus, slot, function, PCI_CFG_INTERFACE) == programif)
       			 	return 1;
        	}
        }
    }
    return 0;
}
