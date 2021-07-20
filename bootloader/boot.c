#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    if(mbdesc->signature[0] == 'M' && mbdesc->signature[1] == 'B')
        SerialPutStr("MBDesc signature check passed\n\r");
    SerialPutStr("Hello from my bootloader\n\r");
    while(1);
}