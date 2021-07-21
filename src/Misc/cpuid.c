#include "cpuid.h"

void _cpuid(uint32_t reg, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
    __asm__ volatile("cpuid"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "0" (reg));
}


char* CPUIDGetBrand() {
	char* name = CPUIDBrandVar;
	_cpuid(0x80000002, (uint32_t *)(name +  0), (uint32_t *)(name +  4), (uint32_t *)(name +  8), (uint32_t *)(name + 12));
	_cpuid(0x80000003, (uint32_t *)(name + 16), (uint32_t *)(name + 20), (uint32_t *)(name + 24), (uint32_t *)(name + 28));
	_cpuid(0x80000004, (uint32_t *)(name + 32), (uint32_t *)(name + 36), (uint32_t *)(name + 40), (uint32_t *)(name + 44));
	name[47] = 0;
	return name;
}

int CPUIDDetect() {
	char* brand = CPUIDGetBrand();
	return brand[0] != 0;
}

int CPUIDIs64Bit() {
    uint32_t eax, ebx, ecx, edx;
    _cpuid(0x80000001, &eax, &ebx, &ecx, &edx);
	return (edx & (1 << 29));
}