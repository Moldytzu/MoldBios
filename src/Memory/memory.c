#include "memory.h"

uint32_t RAMDetect() {
    //Using CMOS to detect memory https://wiki.osdev.org/CMOS#Memory_Size_Registers
    
    uint32_t low =  (((uint16_t) CMOSGetRegister(0x16) << 8) | CMOSGetRegister(0x15));
    uint32_t ext =  (((uint16_t) CMOSGetRegister(0x18) << 8) | CMOSGetRegister(0x17)) / 1024;
    uint32_t xext = (((((uint16_t) CMOSGetRegister(0x35) << 8) | CMOSGetRegister(0x34)) * 65536)/1024/1024);

    if (xext == 0) {
        if(ext != 0)
            return ext+1; //because it shows in range 1 MB - 16 MB and the first MB is not calculated
        SerialPutStr("\n\rMoldBios: Memory detected is lower than 1 MB! Halting\n\r");
        while(1){
            asm ("hlt");
        };    
    } else {
        return xext+16; //because it shows in range 16 MB - 4 GB and the first 16 MB is not calculated
    }  
}