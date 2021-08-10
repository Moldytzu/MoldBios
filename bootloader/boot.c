#include "moldlib.h"

void BEntry(struct MoldBootDescriptor* mbdesc) {
    PutStr("Hello from my beautiful bootloader that now works!\n");

    for(int i = 0;i<=100;i++)
        for(int j = 0;j<=100;j++)
            PutPix(i,j,0xFF00FF);

    PutStr("A pink square should have appeard.\n");
    while(1);
}