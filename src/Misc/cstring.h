#pragma once
#include <stdint.h>
#include "../Memory/memory.h"
#define Buffer1 0x1020 // 32 bytes
#define Buffer2 0x1040 // 32 bytes

int inttostr(uint32_t num);
int strlen(char* str);
int strcmp(const char *s1, const char *s2);
char toupper(char chr);
