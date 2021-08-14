#pragma once
#include "../IO/ports.h"
#include "ramfb.h"

#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64
#define PS2_COMMAND_PORT 0x64

void PS2Init();
uint8_t PS2Detect();
void PS2WaitForKey();
