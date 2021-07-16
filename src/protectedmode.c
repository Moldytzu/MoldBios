#include "Drivers/serial.h"
#include "Drivers/pci.h"
#include "Misc/cstring.h"
#include "Memory/memory.h"
#include "Drivers/ramfb.h"
#include "Drivers/ps2.h"

extern void PMEntry() {
	RAMFBInit(800, 600);

    PCIChipset machineChipset = PCIGetChipset();

    if(machineChipset.Device == Q35_DEVICE && machineChipset.Vendor == Q35_VENDOR)
        RAMFBPutStr("MoldBios: Q35 chipset detected!\n");
    else if(machineChipset.Device == I440FX_DEVICE && machineChipset.Vendor == I440FX_VENDOR)
        RAMFBPutStr("MoldBios: i440FX chipset detected!\n");
    else
        RAMFBPutStr("MoldBios: Unknown chipset! Continue with caution.\n");

    RAMFBPutStr("MoldBios: Detected RAM ");
    RAMFBPutStr(inttostr(RAMDetect()));
    RAMFBPutStr(" MB\n");
    
    PS2Init();
    
    while(1) {
    	asm ("hlt");
    }
}
