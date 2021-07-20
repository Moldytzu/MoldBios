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
#include "IO/eis.h"
#include "Misc/moldboot.h"

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

    RAMFBPutStr("MoldBios: CPUID: ");
    RAMFBPutStr(CPUIDDetect() ? "Supported\n" : "Not supported\n");

    RAMFBPutStr("MoldBios: x87 FPU: ");
    RAMFBPutStr(FPUDetect() ? "Present\n" : "Not present\n");

    RAMFBPutStr("MoldBios: SSE: ");
    RAMFBPutStr(SSEDetect() ? "Supported\n" : "Not supported\n");

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
    	
    if(FloppyGetDrives())
    	FloppyInit(FLOPPY_DRIVE_MASTER);

    if(FPUDetect())
        FPUInit();
    
    RAMFBPutStr("MoldBios: Power On Self Test passed!\n\n");

    PCSpeakerBeep();
    
    if(ATADetect()) {
        RAMFBPutStr("Booting from IDE hard disk\n");
        //Copying first 8 sectors (4 kb) from the hard disk into memory
        for(int i = 0;i<8;i++){
            memcpy(0x300000+(i*0x200),ATAReadLBA(i),512);
        }
        
        struct MoldBootDescriptor mbdesc;

        mbdesc.signature[0] = 'M';
        mbdesc.signature[1] = 'B';

        mbdesc.numEntries = 1;
        mbdesc.entries[0].Address = RAMFBPutStr;
        mbdesc.entries[0].Type = MB_T_PUTSTR;

        void (*boot)(struct MoldBootDescriptor*) = (void (*)(struct MoldBootDescriptor*))0x300000;
        boot(&mbdesc);
    }

    while(1) {
    	asm ("hlt");
    }
}
