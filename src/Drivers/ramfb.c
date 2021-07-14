#include "ramfb.h"

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

void RAMFBInit(int width, int height, int bpp) {
    struct FWCFGFile file;
    FWCFGLocateFile("etc/ramfb", &file);
    if (file.Selector) {
    	SerialPutStr("MoldBios: Detected RAMFB\n\r");
    	SerialPutStr("MoldBios: Needed RAM for the framebuffer is ");
    	SerialPutStr(inttostr((width * (bpp / 8) * height)/1024/1024));
    	SerialPutStr(" MB\n\r");
        
        struct RAMFBStruct RAMFB;
        RAMFB.Width = swapendianness32(width);
        RAMFB.Height = swapendianness32(height);
        RAMFB.Stride = swapendianness32(width * (bpp / 8));
        RAMFB.Address = swapendianness64(0x100000);
        RAMFB.Flags = 0;
        RAMFB.FOURCC = swapendianness32(0x34325241);
        FWCFGWrite(file.Selector, &RAMFB, sizeof(RAMFB), 0);
        
        SerialPutStr("MoldBios: Initialized RAMFB\n\r");
    } else {
    	SerialPutStr("MoldBios: Cannot detect RAMFB\n\r");
    	while(1) {
    		asm ("hlt");
    	}
    }
}
