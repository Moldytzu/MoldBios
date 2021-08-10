#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    MBPopulateAdresses(mbdesc);

    PutStr("H\n");

    PutStr("H\n");

    PutStr("H\n");

    while(1);
}