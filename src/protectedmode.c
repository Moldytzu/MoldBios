#include "Drivers/serial.h"
#include "Drivers/pci.h"
#include "Memory/memory.h"
#include "Drivers/ramfb.h"
#include "Drivers/ps2.h"
#include "Drivers/ahci.h"
#include "Drivers/floppy.h"
#include "IO/speaker.h"
#include "Misc/cpuid.h"
#include "Drivers/atapio.h"

extern void PMEntry() {
    SerialPutStr("MoldBios: Jumped in protected mode!\n");
	RAMFBInit(800, 600);

	RAMFBPutStr(inttostr(CMOSGetHour()));
	RAMFBPutStr(":");
	RAMFBPutStr(inttostr(CMOSGetMinute()));
	RAMFBPutStr("  ");
	RAMFBPutStr(inttostr(CMOSGetDay()));
	RAMFBPutStr("/");
	RAMFBPutStr(inttostr(CMOSGetMonth()));
	RAMFBPutStr("/");
	RAMFBPutStr(inttostr(CMOSGetYear()+2000));
	RAMFBPutStr("\n");

	RAMFBPutStr("MoldBios: Detecting hardware...\n");

    RAMFBPutStr("MoldBios: CPU: ");
    RAMFBPutStr(CPUIDGetBrand());
    RAMFBPutStr("\n");

    RAMFBPutStr("MoldBios: RAM: ");
    RAMFBPutStr(inttostr(RAMDetect()));
    RAMFBPutStr(" MB\n");
    
	RAMFBPutStr("MoldBios: Chipset: ");

    if(IS_Q35)
        RAMFBPutStr("Q35\n");
    else if(IS_I440FX)
        RAMFBPutStr("i440FX\n");
    else if(IS_MICROVM){
        PCSpeakerBeep();
        PCSpeakerBeep();
    	while(1);
    } else {
        PCSpeakerBeep();
        PCSpeakerBeep();
        PCSpeakerBeep();
        while(1);
    }

    RAMFBPutStr("MoldBios: AHCI controller: ");
    RAMFBPutStr(AHCIDetectController() ? "Present\n" : "Not present\n");

    RAMFBPutStr("MoldBios: IDE controller: ");
    RAMFBPutStr(ATADetect() ? "Present\n" : "Not present\n");

    RAMFBPutStr("MoldBios: PS/2 controller: ");
    RAMFBPutStr(PS2Detect() ? "Present\n" : "Not present\n");

    RAMFBPutStr("MoldBios: Floppy drives: ");
    RAMFBPutStr(inttostr(FloppyGetDrives()));
    RAMFBPutStr("\n");

	RAMFBPutStr("MoldBios: Detection complete!\n");
    
    if(PS2Detect())
    	PS2Init();
    	
    if(FloppyGetDrives()) {
    	FloppyInit(FLOPPY_DRIVE_MASTER);
    }
    
    RAMFBPutStr("MoldBios: Power On Self Test passed!\n");

    PCSpeakerBeep();
    
    if(ATADetect()) {
        RAMFBPutStr("Booting from hard disk\n");
        memcpy(0x300100,ATAReadLBA(0),512);
        void (*boot)() = (void (*)())0x300100;
        boot();
    }

    while(1) {
    	asm ("hlt");
    }
}
