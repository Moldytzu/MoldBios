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