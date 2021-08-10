#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    PutStr("Hello from my beautiful bootloader that now works!\n");

    for(int i = 0;i<=100;i++)
        for(int j = 0;j<=100;j++)
            PutPix(i,j,0xFF00FF);

    PutStr("Memory Size: ");
    PutStr(inttostr(mbdesc->hardware.MemoryMap.FreeEnd / 1024 / 1024 + 1));
    PutStr(" MB\n");
    while(1);
}