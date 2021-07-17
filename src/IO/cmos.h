#pragma once
#include "ports.h"

#define bcdtobin(x) (x & 0x0F) + ((x / 16) * 10)

static inline uint8_t CMOSGetRegister(uint16_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}

static inline uint8_t CMOSGetSecond() {
	uint8_t val = CMOSGetRegister(0x0);
	if(!(CMOSGetRegister(0x0B)& 0x04))
		val = bcdtobin(val);
	return val;
}

static inline uint8_t CMOSGetMinute() {
	uint8_t val = CMOSGetRegister(0x2);
	if(!(CMOSGetRegister(0x0B)& 0x04))
		val = bcdtobin(val);
	return val;
}

static inline uint8_t CMOSGetHour() {
	uint8_t val = CMOSGetRegister(0x4);
	if(!(CMOSGetRegister(0x0B)& 0x04))
		val = bcdtobin(val);
	return val;
}

static inline uint8_t CMOSGetDay() {
	uint8_t val = CMOSGetRegister(0x7);
	if(!(CMOSGetRegister(0x0B)& 0x04))
		val = bcdtobin(val);
	return val;
}

static inline uint8_t CMOSGetMonth() {
	uint8_t val = CMOSGetRegister(0x8);
	if(!(CMOSGetRegister(0x0B)& 0x04))
		val = bcdtobin(val);
	return val;
}

static inline uint8_t CMOSGetYear() {
	uint8_t val = CMOSGetRegister(0x9);
	if(!(CMOSGetRegister(0x0B)& 0x04))
		val = bcdtobin(val);
	return val;
}
