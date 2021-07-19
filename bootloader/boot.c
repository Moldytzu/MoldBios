#include <stdint.h>

extern void BEntry() {
    asm volatile("out %0, %1" :: "a"('H'), "Nd"(0x3F8));
    asm volatile("out %0, %1" :: "a"('i'), "Nd"(0x3F8));
    asm volatile("out %0, %1" :: "a"('!'), "Nd"(0x3F8));
    while(1);
}