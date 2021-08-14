#include "moldlib.h"

uint16_t Signature = 0xDEAD;

void BEntry(struct MoldBootDescriptor* mbdesc) {
    SetColor(WHITE);
    PutStr("White\n");
    SetColor(BLACK);
    PutStr("Black\n");
    SetColor(RED);
    PutStr("Red\n");
    SetColor(GREEN);
    PutStr("Green\n");
    SetColor(BLUE);
    PutStr("Blue\n");
    SetColor(YELLOW);
    PutStr("Yellow\n");
    SetColor(MAGENTA);
    PutStr("Magenta\n");
    SetColor(CYAN);
    PutStr("Cyan\n");
    SetColor(ORANGE);
    PutStr("Orange\n");
    SetColor(WHITE);

    for(int i = 500;i<=600;i++)
        for(int j = 200;j<=300;j++)
            PutPix(i,j,0xFF00FF);

    PutStr("Memory Size: ");
    PutStr(inttostr(mbdesc->hardware.MemoryMap.FreeEnd / 1024 / 1024 + 1));
    PutStr(" MB\n");

    char buffer[512];
    PutStr("First disk sector: ");
    PutStr(ReadDisk(0,buffer));

    for(int i = 0;i<=800;i++) {
        for(int j = 0;j<=600;j++) {
            //PutPix(i,j,i*0xF+j*0xF);
            for(volatile int i = 0;i<0xFFF;i++) asm volatile ("nop"); //delay
        }
    }

    while(1);
}