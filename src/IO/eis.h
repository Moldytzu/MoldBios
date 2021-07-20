#pragma once
#include <stdint.h>
#include "../Drivers/ramfb.h"
#include "../Misc/cpuid.h"

//Extended Instruction Set

//x87 FPU
int FPUDetect();
void FPUInit();

//SSE
int SSEDetect();
