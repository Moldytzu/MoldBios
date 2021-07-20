#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    if(mbdesc->signature[0] == 'M' && mbdesc->signature[1] == 'B')
        SerialPutStr("MBDesc signature check passed\n\r");

    for(int i = 0;i<mbdesc->numEntries;i++){
        if(mbdesc->entries[i].Type == 0){
            ((void (*)(char*))mbdesc->entries[i].Address)("Hello from bootloader in RAMFB");
        }
    }

    SerialPutStr("Hello from the bootloader in serial console\n\r");


    while(1);
}