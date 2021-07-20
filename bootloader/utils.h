#pragma once
#include <stdint.h>

static void SerialPutStr(char* str) {
    for(int i = 0;str[i] != 0;i++)
        asm volatile("out %0, %1" :: "a"(str[i]), "Nd"(0x3F8));
}