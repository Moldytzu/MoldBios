#pragma once
#include <stdint.h>
#include "../IO/cmos.h"
#include "../Drivers/serial.h"
#include "../Misc/cstring.h"
#include "../IO/speaker.h"

uint32_t RAMDetect();
void* memcpy (void *dest, const void *src, uint32_t len);
void memset (void* dest, int val, uint32_t len);
