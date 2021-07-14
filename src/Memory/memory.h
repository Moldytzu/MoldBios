#pragma once
#include <stdint.h>
#include "../IO/cmos.h"
#include "../Drivers/serial.h"
#include "../Misc/cstring.h"

uint32_t RAMDetect();
void* memcpy (void *dest, const void *src, uint32_t len);
