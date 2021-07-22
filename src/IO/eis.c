#include "eis.h"

int FPUDetect() {
    uint32_t cr0;
    asm volatile ("mov %%cr0,%0" : "=r"(cr0));
    return !(cr0 & 0xF00);
}

void FPUInit() {
    RAMFBPutStr("MoldBios: Initializing x87 FPU!\n");
    asm volatile ("finit");
    RAMFBPutStr("MoldBios: Initialized x87 FPU!\n");
}

int SSEDetect() {
    uint32_t eax, ebx, ecx, edx;
    _cpuid(0x1, &eax, &ebx, &ecx, &edx);
    return (ebx & (1 << 25)) | (ebx & (1 << 26)) | (ecx & (1 << 0)) | (ecx & (1 << 19)) | (ecx & (1 << 20));
}

void SSEInit() {
    RAMFBPutStr("MoldBios: Initializing SSE!\n");
    uint32_t tmp;
    asm volatile ("mov %%cr0, %0" : "=r"(tmp));
    tmp &= 0xFFFB;
    tmp |= 2;
    asm volatile ("mov %0, %%cr0" :: "r"(tmp));
    asm volatile ("mov %%cr4, %0" : "=r"(tmp));
    tmp |= 3 << 9;
    asm volatile ("mov %0, %%cr4" :: "r"(tmp));
    RAMFBPutStr("MoldBios: Initialized SSE!\n");
}

int AVXDetect() {
    uint32_t eax, ebx, ecx, edx;
    _cpuid(0x1, &eax, &ebx, &ecx, &edx);
    return (ecx & (1 << 28)); 
}

void AVXInit() {
    RAMFBPutStr("MoldBios: Initializing AVX!\n");
    uint32_t tmp = 0;
    asm volatile ("mov %0,%%ecx" : "=r"(tmp));
    asm volatile ("xgetbv");
    asm volatile ("mov %%eax,%0" : "=r"(tmp));
    tmp |= 7;
    asm volatile ("mov %0,%%eax" : "=r"(tmp));
    asm volatile ("xsetbv");
    RAMFBPutStr("MoldBios: Initialized AVX!\n");
}