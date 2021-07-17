#include "floppy.h"

uint8_t FloppyGetDrives() {
	uint8_t drives = CMOSGetRegister(0x10); // Result is in this form: first nibble is the slave floppy type and the second nibble is the master floppy type
	uint8_t master = ((drives >> 4) & 0x0F);
	uint8_t slave =  (drives & 0x0F);
	if(master == 0 && slave == 0)
		return 0;
	else if ((master > 0 && slave == 0) || (master == 0 && slave > 0))
		return 1;
	return 2;
}

void FloppyDoCommand(uint8_t command) {
    for(int i = 0; i < 0xFFFF; i++) {
        if(inb(FLOPPY_BASE_PORT+FLOPPY_MSR_REG) & 0x80) { //check if controller is ready
            outb(FLOPPY_BASE_PORT+FLOPPY_FIFO_REG, command);
            return;
        }
    }
}

uint8_t FloppyReadFIFO() {
    for(int i = 0; i < 0xFFFF; i++) {
        if(inb(FLOPPY_BASE_PORT+FLOPPY_MSR_REG) & 0x80) { //check if controller is ready
            return inb(FLOPPY_BASE_PORT+FLOPPY_FIFO_REG);
        }
    }
}

void FloppySenseIntrerrupt(uint8_t* cylinder,uint8_t* status) {
	FloppyDoCommand(FLOPPY_SENSE_COMMAND);
	*status = FloppyReadFIFO();
	*cylinder = FloppyReadFIFO();
}

void FloppyStartMotor() {
	outb(FLOPPY_BASE_PORT + FLOPPY_DOR_REG, 0x1C);
}

void FloppyStopMotor() {
	outb(FLOPPY_BASE_PORT + FLOPPY_DOR_REG, 0x0C);
}

void FloppyCalibrate(uint8_t drive) {
	FloppyStartMotor();
	
	for(int i = 0; i < 10;i++) {
		FloppyDoCommand(FLOPPY_RECALIBRATE_COMMAND);
		FloppyDoCommand(drive);
		for(int j = 0; j < 0xFFFF; j++);
		int cylinder,status;
		FloppySenseIntrerrupt(&cylinder,&status);
        if(!cylinder) {
            FloppyStopMotor();
            return;
        }
	}
}

void FloppyFlushIntrerrupt() {
	int tmp;
	FloppySenseIntrerrupt(&tmp, &tmp);
}

void FloppyInit(uint8_t drive) {
	RAMFBPutStr("MoldBios: Initializing floppy!\n");
	outb(FLOPPY_BASE_PORT + FLOPPY_DOR_REG, 0x00); //Disable controller
	outb(FLOPPY_BASE_PORT + FLOPPY_DOR_REG, 0x0C); //Enable controller
	for(int j = 0; j < 0xFFFF; j++);
	FloppyFlushIntrerrupt();
	outb(FLOPPY_BASE_PORT + FLOPPY_CCR_REG, 0x00); //Set transfer speed
	FloppyDoCommand(FLOPPY_SPECIFY_COMMAND);
	FloppyDoCommand(0xDF);
	FloppyDoCommand(0x02);
	FloppyCalibrate(drive);
	RAMFBPutStr("MoldBios: Initialized floppy!\n");
}
