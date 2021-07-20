#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    globalMBDesc = mbdesc;

    PutStr("Hello from bootloader!");

    while(1);
}