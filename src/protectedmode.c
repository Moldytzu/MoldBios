#include "Drivers/serial.h"
#include "Drivers/pci.h"
#include "Misc/cstring.h"
#include "Memory/memory.h"
#include "Drivers/ramfb.h"
#include "Drivers/ps2.h"
#include "Drivers/ahci.h"
#include "Drivers/floppy.h"
#include "IO/speaker.h"
#include "Misc/cpuid.h"

extern void PMEntry() {
	RAMFBInit(800, 600);

	RAMFBPutStr(inttostr(CMOSGetHour()));
	RAMFBPutStr(":");
	RAMFBPutStr(inttostr(CMOSGetMinute()));
	RAMFBPutStr("  ");
	RAMFBPutStr(inttostr(CMOSGetDay()));
	RAMFBPutStr("/");
	RAMFBPutStr(inttostr(CMOSGetMonth()));
	RAMFBPutStr("/");
	RAMFBPutStr(inttostr(CMOSGetYear()));
	RAMFBPutStr("\n");

	RAMFBPutStr("MoldBios: Detecting hardware...\n");

	RAMFBPutStr("MoldBios: Chipset: ");

    PCIChipset machineChipset = PCIGetChipset();

    if(machineChipset.Device == Q35_DEVICE && machineChipset.Vendor == Q35_VENDOR)
        RAMFBPutStr("Q35\n");
    else if(machineChipset.Device == I440FX_DEVICE && machineChipset.Vendor == I440FX_VENDOR)
        RAMFBPutStr("i440FX\n");
    else if(machineChipset.Device == MICROVM_VENDOR_DEVICE && machineChipset.Vendor == MICROVM_VENDOR_DEVICE){
        PCSpeakerBeep();
        PCSpeakerBeep();
    	while(1);
    } else {
        PCSpeakerBeep();
        PCSpeakerBeep();
        PCSpeakerBeep();
        while(1);
    }

    RAMFBPutStr("MoldBios: RAM: ");
    RAMFBPutStr(inttostr(RAMDetect()));
    RAMFBPutStr(" MB\n");
    
    RAMFBPutStr("MoldBios: CPU: ");
    RAMFBPutStr(CPUIDGetBrand());
    RAMFBPutStr("\n");
    
    RAMFBPutStr("MoldBios: AHCI controller: ");
    RAMFBPutStr(AHCIDetectController() ? "Present\n" : "Not present\n");

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
    
    PCSpeakerBeep();
    
    while(1) {
    	asm ("hlt");
    }
}
