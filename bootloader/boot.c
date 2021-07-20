#include <stdint.h>

extern void BEntry() {
    SerialPutStr("Hello from my bootloader!\n\r");
    while(1);
}

void SerialPutStr(char* chr) {
    for(int i = 0;chr[i] != 0;i++)
        asm volatile("out %0, %1" :: "a"(chr[i]), "Nd"(0x3F8));
}