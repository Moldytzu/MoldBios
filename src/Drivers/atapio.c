#include "atapio.h"

char* ATAReadLBA(uint32_t lba) {
    outb(ATA_MASTER + 6, 0xE0 | ((lba >> 24) & 0x0F)); //drive/head register, enable lba and add bits 24 to 27 of lba
    outb(ATA_MASTER + 1, 0);
    outb(ATA_MASTER + 2, 1); //set to 1 sector
    outb(ATA_MASTER + 3, lba); //lba
    outb(ATA_MASTER + 4, lba >> 8); //lba
    outb(ATA_MASTER + 5, lba >> 16); //lba
    outb(ATA_MASTER + 7, ATA_READ_SECTORS_COMMAND); //send command
    while (!(inb(ATA_MASTER + 7) & 8)); //wait for busy flag

    for (int i = 0; i < 256; i++) {
        uint16_t val = inw(ATA_MASTER); //get value
        *((uint8_t*)ATA_BUFFER + i * 2) = val & 0xff;
        *((uint8_t*)ATA_BUFFER + i * 2 + 1) = val >> 8;
    }

    return ATA_BUFFER;
}

int ATADetect() {
    return PCIFindDeviceW(0x1, 0x1);
}