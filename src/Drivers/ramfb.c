#include "ramfb.h"
#include "../IO/speaker.h"
#include "../Misc/bmpfont.h"
int FWCFGLocateFile(char *filename, struct FWCFGFile *info) {
    uint32_t items;
    uint32_t offset = 0;
    FWCFGRead(FWCFG_ROOT, &items, sizeof(uint32_t), offset);
    offset += sizeof(uint32_t);
    items = swapendianness32(items);
    for (; offset < items * sizeof(struct FWCFGFile); offset += sizeof(struct FWCFGFile)) {
        struct FWCFGFile file;
        FWCFGRead(FWCFG_ROOT, &file, sizeof(struct FWCFGFile), offset);
        if (!strcmp(file.Name, filename)) {
            info->Selector = swapendianness16(file.Selector);
            info->Size = swapendianness32(file.Size);
            memcpy(&info->Name, file.Name, 56);
            return 0;
        }
    }
    return -1;
}

void FWCFGRead(uint16_t selector, void *buf, uint32_t len, uint32_t offset) {
    volatile struct FWCFGCommand command;
    command.Control = swapendianness32(((uint32_t) selector << 16) | FWCFGCommand_SKIP | FWCFGCommand_SELECT);
    command.Length = swapendianness32(offset);
    outd(FWCFG_DMA_PORT, swapendianness32((uint32_t) &command));
    while (command.Control & ~FWCFGCommand_ERROR);
    command.Control = swapendianness32(((uint32_t) selector << 16) | FWCFGCommand_READ);
    command.Length = swapendianness32(len);
    command.Address = swapendianness64((uint64_t) buf);
    outd(FWCFG_DMA_PORT, swapendianness32((uint32_t) &command));
    while (command.Control & ~FWCFGCommand_ERROR);
}

void FWCFGWrite(uint16_t selector, const void *buf, uint32_t len, uint32_t offset) {
    volatile struct FWCFGCommand command;
    command.Control = swapendianness32(((uint32_t) selector << 16) | FWCFGCommand_SKIP | FWCFGCommand_SELECT);
    command.Length = swapendianness32(offset);
    outd(FWCFG_DMA_PORT, swapendianness32((uint32_t) &command));
    while (command.Control & ~FWCFGCommand_ERROR);
    command.Control = swapendianness32(((uint32_t) selector << 16) | FWCFGCommand_WRITE);
    command.Length = swapendianness32(len);
    command.Address = swapendianness64((uint64_t) buf);
    outd(FWCFG_DMA_PORT, swapendianness32((uint32_t) &command));
    while (command.Control & ~FWCFGCommand_ERROR);
}

void RAMFBPutPix(int x,int y, uint32_t clr) {
	*(uint32_t*)(x*4 + (ScreenW*y *4) + VideoMemory) = clr;
}

void RAMFBPutRectF(int x,int y, int w, int h, uint32_t clr) {
	for(int i = x; i < (x+w); i++)
		for(int j = y; j < (y+h); j++)
			RAMFBPutPix(i,j,clr);
}

void RAMFBPutRect(int x,int y, int w, int h, uint32_t clr) {
	RAMFBPutRectF(x,y,w,1,clr);
	RAMFBPutRectF(x,y+h,w,1,clr);
	RAMFBPutRectF(x,y,1,h,clr);
	RAMFBPutRectF(x+w,y,1,h,clr);
}

void RAMFBPutChar(int x, int y, char chr) {
    for (uint32_t yy = 0; yy < 8; yy++) {
        for (uint32_t xx = 0; xx < 8; xx++) {
            if (BitmapFont[chr][yy] & (1 << xx)) {
                RAMFBPutRectF(x + xx*FontScaling, y + yy*FontScaling,FontScaling,FontScaling,0xFFFFFF);
            }
        }
    }
}

void RAMFBPutStr(char* str) {
	for(int i = 0; str[i] != 0; i++) {
		if (CursorX+8*FontScaling >= ScreenW) {
			CursorY+=9*FontScaling;
			CursorX = 0;
		}
		if (str[i] == '\n') {
			CursorY+=9*FontScaling;
			CursorX = 0;
		} else {
			RAMFBPutChar(CursorX,CursorY,str[i]);
			CursorX+=8*FontScaling;
		}
	}
}

void RAMFBInit(int width, int height) {	
    struct FWCFGFile file;
    FWCFGLocateFile("etc/ramfb", &file); //get the ramfb file
    if (file.Selector) { //if exists use it
    	SerialPutStr("MoldBios: Detected RAMFB\n");
        
        struct RAMFBStruct RAMFB = {0};
        RAMFB.Width = swapendianness32(width);
        RAMFB.Height = swapendianness32(height);
        RAMFB.Stride = swapendianness32(width * (32 / 8));
        RAMFB.Address = swapendianness64(VideoMemory);
        RAMFB.FOURCC = swapendianness32(0x34325241);
        FWCFGWrite(file.Selector, &RAMFB, sizeof(RAMFB), 0); //copy the struct
        
        CursorX = 0;
        CursorY = 0;
        ScreenW = width;
        ScreenH = height;
        
        memset(VideoMemory,0,VideoMemory);
        
        SerialPutStr("MoldBios: Initialized RAMFB\n");
    } else {
    	SerialPutStr("MoldBios: Cannot detect RAMFB\n");
    	
    	PCSpeakerBeep();
    	PCSpeakerBeep();
    	PCSpeakerBeep();
    	PCSpeakerBeep();
    	
    	asm volatile ("hlt");
    }
}
