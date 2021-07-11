#include "Drivers/serial.h"
#include "Drivers/pci.h"
#include "Misc/cstring.h"

extern void PMEntry() {
    PCIChipset machineChipset = PCIGetChipset();

    if(machineChipset.Device == Q35_DEVICE && machineChipset.Vendor == Q35_VENDOR)
        SerialPutStr("MoldBios: Q35 chipset detected!\n\r");
    else if(machineChipset.Device == I440FX_DEVICE && machineChipset.Vendor == I440FX_VENDOR)
        SerialPutStr("MoldBios: i440FX chipset detected!\n\r");

    SerialPutStr(inttostr(0x100));
    SerialPutStr("\n\r");
    while(1);
}