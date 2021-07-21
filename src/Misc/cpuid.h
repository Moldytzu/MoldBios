#pragma once
#include <stdint.h>

#define CPUIDBrandVar 0x1060 //size of 48 * 1 byte

int CPUIDIs64Bit();
char* CPUIDGetBrand();
void _cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);