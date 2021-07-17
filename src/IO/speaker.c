#include "speaker.h"

uint8_t PCSpeakerPlay() {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / 1000;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
}

void PCSpeakerStop() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
}

void PCSpeakerBeep() {
	PCSpeakerPlay();
	for(volatile int i = 0;i<0xFFFFFF;i++) asm volatile ("nop");
	PCSpeakerStop();
	for(volatile int i = 0;i<0xFFFFFF;i++) asm volatile ("nop");
}
