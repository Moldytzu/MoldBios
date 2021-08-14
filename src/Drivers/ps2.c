#include "ps2.h"

void PS2WaitResponse() {
	while (!(inb(PS2_STATUS_PORT) & 1)); //Wait for bit 1 to be set (Output buffer status)
}

void PS2WaitInput() {
	while (inb(PS2_STATUS_PORT) & 2); //Wait for bit 2 to be set (Input buffer status)
}

uint8_t PS2Test() {
	outb(PS2_COMMAND_PORT,0xAA); //Self test
	PS2WaitResponse();
	return inb(PS2_DATA_PORT) == 0x55;
}
uint8_t PS2WaitForKey() {
	const char ScanCodeSet1[] = {0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b',0,'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' '};
    while(1) {
		uint8_t c = inb(0x60);
        if(c > 0) return ScanCodeSet1[c];
    }
}

uint8_t PS2Detect() {
	//Detect if PS/2 is present by self testing it
	return PS2Test();
}

uint8_t PS2GetConfig() {
	PS2WaitInput();
	outb(PS2_COMMAND_PORT,0x20); //Get Config
	PS2WaitResponse();
	return inb(0x60);	
}

void PS2SetConfig(uint8_t cfg) {
	PS2WaitInput();
	outb(PS2_COMMAND_PORT,0x60); //Set Config
	PS2WaitInput();
	outb(0x60,cfg);	
}

void PS2Init() {
	RAMFBPutStr("MoldBios: Initializing PS/2 controller!\n");
	
	outb(PS2_COMMAND_PORT,0xAD); //Disable first port
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xA7); //Disable second port
	PS2WaitInput();
	
	inb(PS2_DATA_PORT); //Flush data
	
	PS2SetConfig(PS2GetConfig() & ~1); //Disable IRQs
	PS2SetConfig(PS2GetConfig() & ~(1 << 1));
	
	PS2SetConfig(PS2GetConfig() & ~(1 << 6)); //Disable translation
	
	PS2Test(); //Self test
	
	outb(PS2_COMMAND_PORT,0xAE); //Enable first port
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xA8); //Enable second port
	PS2WaitInput();
	
	PS2SetConfig(PS2GetConfig() | 1); //Enable IRQs
	PS2SetConfig(PS2GetConfig() | (1 << 1));

	PS2SetConfig(PS2GetConfig() | (1 << 6)); //Enable translation

	outb(PS2_COMMAND_PORT,0xFF); //Reset Keyboard
	PS2WaitInput();
	
	outb(PS2_COMMAND_PORT,0xD3);
	PS2WaitInput();
	outb(PS2_COMMAND_PORT,0xFF); //Reset Mouse
	PS2WaitInput();

	RAMFBSetColor(0xFFF000);
	RAMFBPutStr("MoldBios: Press any key to continue!\n");
	PS2WaitResponse();

	RAMFBSetColor(0xFFFFFF);
	
	RAMFBPutStr("MoldBios: PS/2 controller initialized!\n");
}
