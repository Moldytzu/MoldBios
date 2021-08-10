#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    PutStr("Hello from my beautiful bootloader that now works!\n");

    while(1);
}