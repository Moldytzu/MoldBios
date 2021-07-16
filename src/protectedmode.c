#include "Drivers/serial.h"
#include "Drivers/pci.h"
#include "Misc/cstring.h"
#include "Memory/memory.h"
#include "Drivers/ramfb.h"
#include "Drivers/ps2.h"
#include "Drivers/ahci.h"

extern void PMEntry() {
	RAMFBInit(800, 600);

	RAMFBPutStr("MoldBios: Detecting hardware!\n");

    PCIChipset machineChipset = PCIGetChipset();

    if(machineChipset.Device == Q35_DEVICE && machineChipset.Vendor == Q35_VENDOR)
        RAMFBPutStr("MoldBios: Q35 chipset detected!\n");
    else if(machineChipset.Device == I440FX_DEVICE && machineChipset.Vendor == I440FX_VENDOR)
        RAMFBPutStr("MoldBios: i440FX chipset detected!\n");
    else if(machineChipset.Device == MICROVM_VENDOR_DEVICE && machineChipset.Vendor == MICROVM_VENDOR_DEVICE)
    	RAMFBPutStr("MoldBios: MicroVM chipset detected!\n");
    else {
        RAMFBPutStr("MoldBios: Unknown chipset! Vendor: ");
        RAMFBPutStr(inttostr(machineChipset.Vendor));
        RAMFBPutStr("  Device: ");
        RAMFBPutStr(inttostr(machineChipset.Device));
        RAMFBPutStr("\n");
        while(1);
    }

    RAMFBPutStr("MoldBios: Detected RAM: ");
    RAMFBPutStr(inttostr(RAMDetect()));
    RAMFBPutStr(" MB\n");
    
    RAMFBPutStr("MoldBios: AHCI controller: ");
    RAMFBPutStr(AHCIDetectController() ? "Present\n" : "Not present\n");


	RAMFBPutStr("MoldBios: Detection complete!\n");
    
    PS2Init();
    
    while(1) {
    	asm ("hlt");
    }
}
