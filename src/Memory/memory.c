#include "memory.h"

uint32_t RAMDetect() {
    //Using CMOS to detect memory https://wiki.osdev.org/CMOS#Memory_Size_Registers
    uint32_t low =  (((uint16_t) CMOSGetRegister(0x16) << 8) | CMOSGetRegister(0x15)) / 1024;
    uint32_t ext =  (((uint16_t) CMOSGetRegister(0x30) << 8) | CMOSGetRegister(0x31)) / 1024;
    uint32_t xext = ((((uint16_t) CMOSGetRegister(0x35) << 8) | CMOSGetRegister(0x34)) * 65536)/1024/1024;

    return xext+16;
}