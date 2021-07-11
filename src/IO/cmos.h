#pragma once
#include "ports.h"

static inline uint8_t CMOSGetRegister(uint16_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}