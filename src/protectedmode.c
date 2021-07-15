#include "Drivers/serial.h"
#include "Drivers/pci.h"
#include "Misc/cstring.h"
#include "Memory/memory.h"
#include "Drivers/ramfb.h"

extern void PMEntry() {
    PCIChipset machineChipset = PCIGetChipset();

    if(machineChipset.Device == Q35_DEVICE && machineChipset.Vendor == Q35_VENDOR)
        SerialPutStr("MoldBios: Q35 chipset detected!\n");
    else if(machineChipset.Device == I440FX_DEVICE && machineChipset.Vendor == I440FX_VENDOR)
        SerialPutStr("MoldBios: i440FX chipset detected!\n");
    else
        SerialPutStr("MoldBios: Unknown chipset! Continue with caution.\n");

    SerialPutStr("MoldBios: Detected RAM ");
    SerialPutStr(inttostr(RAMDetect()));
    SerialPutStr(" MB\n");
    
    RAMFBInit(800, 600); 
	
	RAMFBPutStr("MoldBios: Initialized RAMFB!\n");
	RAMFBPutStr("MoldBios: Detected RAM ");
	RAMFBPutStr(inttostr(RAMDetect()));
	RAMFBPutStr(" MB\n");
	

    while(1) {
    	asm ("hlt");
    }
}
