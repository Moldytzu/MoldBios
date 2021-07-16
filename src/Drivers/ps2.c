#include "ps2.h"

void PS2WaitResponse() {
	while (!(inb(PS2_STATUS_PORT) & 1)); //Wait for bit 1 to be set (Output buffer status)
}

void PS2WaitInput() {
	while (inb(PS2_STATUS_PORT) & 2); //Wait for bit 2 to be set (Input buffer status)
}

void PS2Init() {
	RAMFBPutStr("MoldBios: Initializing PS/2 controller!\n");
	
	outb(PS2_COMMAND_PORT,0xAD); //Disable first port
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xA7); //Disable second port
	PS2WaitInput();
	
	inb(PS2_DATA_PORT); //Flush data
	
	outb(PS2_COMMAND_PORT,0xAA); //Self test
	PS2WaitResponse();
	if(inb(PS2_DATA_PORT) != 0x55) { //Check if the test failed
		RAMFBPutStr("MoldBios: PS/2 controller self-test failed!\n");
		while(1);
	}
	
	outb(PS2_COMMAND_PORT,0xAE); //Enable first port
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xA8); //Enable second port
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xFF); //Reset Keyboard
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xD3);
	PS2WaitInput();
	outb(PS2_COMMAND_PORT,0xFF); //Reset Mouse
	PS2WaitInput();
	
	RAMFBPutStr("MoldBios: PS/2 controller initialized!\n");
}
