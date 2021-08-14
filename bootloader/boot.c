#include "moldlib.h"

uint16_t Signature = 0xDEAD;

void BEntry(struct MoldBootDescriptor* mbdesc) {
    PutStr("Hello from my beautiful bootloader that now works!\n");

    for(int i = 500;i<=600;i++)
        for(int j = 200;j<=300;j++)
            PutPix(i,j,0xFF00FF);

    PutStr("Memory Size: ");
    PutStr(inttostr(mbdesc->hardware.MemoryMap.FreeEnd / 1024 / 1024 + 1));
    PutStr(" MB\n");

    PutStr("Disk Contents: ");
    PutStr(ReadDisk(0));
    
    while(1);
}