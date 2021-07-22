#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    MBPopulateAdresses(mbdesc);

    PutStr("Hello from bootloader!\n");

    while(1);
}