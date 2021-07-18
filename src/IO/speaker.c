#include "speaker.h"

uint8_t PCSpeakerPlay() {
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (1193) );
 	outb(0x42, (uint8_t) (1193 >> 8));
 	outb(0x61, inb(0x61) | 3);
}

void PCSpeakerStop() {
 	outb(0x61, inb(0x61) & 0xFC);
}

void PCSpeakerBeep() {
	PCSpeakerPlay();
	for(volatile int i = 0;i<0xFFFFFF;i++) asm volatile ("nop");
	PCSpeakerStop();
	for(volatile int i = 0;i<0xFFFFFF;i++) asm volatile ("nop");
}
