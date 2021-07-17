#include "ramfb.h"

uint32_t cursorX = 0;
uint32_t cursorY = 0;

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
	*(uint32_t*)(x*4 + (800*y *4) + VideoMemory) = clr;
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

#define FontScaling 1 //110%
void RAMFBPutChar(int x, int y, char chr) {
	//8x8 chars
	switch(chr) {
		case 'a':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'b':
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+5*FontScaling,y,1*FontScaling,5*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,5*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			break;
		case 'c':
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case 'd':
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,5*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,5*FontScaling,1*FontScaling,0xFFFFFF);
			
			for(int i=5*FontScaling;i<=7*FontScaling;i++)
				RAMFBPutPix(x+i,y+i-4*FontScaling,0xFFFFFF);
			
			for(int i=7*FontScaling,j=4*FontScaling;i>=5*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case 'e':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case 'f':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'g':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+4*FontScaling,y+4*FontScaling,4*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			break;
		case 'h':
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'i':
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'j':
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			break;
		case 'k':
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			
			for(int i=4*FontScaling,j=0;i>=1*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			
			for(int i=1*FontScaling;i<=4*FontScaling;i++)
				RAMFBPutPix(x+i,y+i+3*FontScaling,0xFFFFFF);
			break;
		case 'l':
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case 'm':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'n':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'p':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,4*FontScaling,0xFFFFFF);
			break;
		case 'q':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,4*FontScaling,0xFFFFFF);
			break;
		case 'r':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,4*FontScaling,0xFFFFFF);
			for(int i = 8*FontScaling;i>=5*FontScaling;i--)
				RAMFBPutPix(x+i,y+i-1*FontScaling,0xFFFFFF);
			break;
		case 's':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			for(int i =1*FontScaling;i<=3*FontScaling;i++)
				RAMFBPutPix(x,y+i,0xFFFFFF);
			RAMFBPutRectF(x+1*FontScaling,y+4*FontScaling,6*FontScaling,1*FontScaling,0xFFFFFF);
			for(int i =5*FontScaling;i<=7*FontScaling;i++)
				RAMFBPutPix(x+7*FontScaling,y+i,0xFFFFFF);
			break;
		case 't':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'u':
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'v':
			RAMFBPutPix(x,y+1*FontScaling,0xFFFFFF);
			
			for(int i = 1*FontScaling;i<=4*FontScaling;i++)
				RAMFBPutPix(x+i,y+i+1*FontScaling,0xFFFFFF);
			
			for(int i=8*FontScaling,j=1*FontScaling;i>=5*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case 'w':
			RAMFBPutPix(x,y+1*FontScaling,0xFFFFFF);
			
			for(int i = 1*FontScaling;i<=4*FontScaling;i++)
				RAMFBPutPix(x+i,y+i+1*FontScaling,0xFFFFFF);
			
			for(int i=8*FontScaling,j=1*FontScaling;i>=5*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case 'x':
			for(int i = 1*FontScaling;i<=7*FontScaling;i++)
				RAMFBPutPix(x+i,y+i,0xFFFFFF);
			
			for(int i=7*FontScaling,j=1*FontScaling;i>=1*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case 'y':
			for(int i = 1*FontScaling;i<=5*FontScaling;i++)
				RAMFBPutPix(x+i,y+i,0xFFFFFF);
			RAMFBPutRectF(x+5*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			break;
		case 'z':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			for(int i=7*FontScaling,j=1*FontScaling;i>1*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case '0':
			RAMFBPutRect(x,y,7*FontScaling,7*FontScaling,0xFFFFFF);
			RAMFBPutPix(x+4*FontScaling,y+3*FontScaling,0xFFFFFF);
			break;
		case '1':
			RAMFBPutRectF(x,y,4*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '2':
			RAMFBPutRectF(x,y,7*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+1*FontScaling,y+7*FontScaling,7*FontScaling,1*FontScaling,0xFFFFFF);
			for(int i=7*FontScaling,j=1*FontScaling;i>1*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case '3':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+8*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '4':
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			for(int i=4*FontScaling,j=0*FontScaling;i>0*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case '5':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,7*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+7*FontScaling,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '6':
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,7*FontScaling,1*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+7*FontScaling,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '7':
			for(int i=7*FontScaling,j=1*FontScaling;i>=1*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			RAMFBPutRectF(x,y,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '8':
			RAMFBPutRect(x,y,7*FontScaling,7*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '9':
			RAMFBPutRect(x,y,7*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x+7*FontScaling,y+4*FontScaling,1*FontScaling,4*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+7*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '+':
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,8*FontScaling,0xFFFFFF);
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case '-':
			RAMFBPutRectF(x,y+4*FontScaling,8*FontScaling,1*FontScaling,0xFFFFFF);
			break;
		case ' ':
			break;
		case '.':
			RAMFBPutPix(x+4*FontScaling,y+7*FontScaling,0xFFFFFF);
			break;
		case '!':
			RAMFBPutRectF(x+4*FontScaling,y,1*FontScaling,5*FontScaling,0xFFFFFF);
			RAMFBPutPix(x+4*FontScaling,y+7*FontScaling,0xFFFFFF);
			break;
		case ':':
			RAMFBPutPix(x+4*FontScaling,y+6*FontScaling,0xFFFFFF);
			RAMFBPutPix(x+4*FontScaling,y+2*FontScaling,0xFFFFFF);
			break;
		case '/':
			for(int i=7*FontScaling,j=1*FontScaling;i>=1*FontScaling;i--,j++)
				RAMFBPutPix(x+i,y+j,0xFFFFFF);
			break;
		case '\\':
			for(int i = 1*FontScaling;i<=7*FontScaling;i++)
				RAMFBPutPix(x+i,y+i,0xFFFFFF);
			break;
		default:
			RAMFBPutRect(x,y,7*FontScaling,7*FontScaling,0xFFFFFF);
			break;
			
		//todo: add support more special characters
	}

}

void RAMFBPutStr(char* str) {
	for(int i = 0; str[i] != 0; i++) {
		if (CursorX+10 >= ScreenW) {
			CursorY+=10*FontScaling;
			CursorX = 0;
		}
		if (str[i] == '\n') {
			CursorY+=10*FontScaling;
			CursorX = 0;
		} else {
			RAMFBPutChar(CursorX,CursorY,toupper(str[i]));
			CursorX+=10*FontScaling;
		}
	}
}

void RAMFBInit(int width, int height) {	
    struct FWCFGFile file;
    FWCFGLocateFile("etc/ramfb", &file); //get the ramfb file
    if (file.Selector) { //if exists use it
    	SerialPutStr("MoldBios: Detected RAMFB\n");
    	SerialPutStr("MoldBios: Needed RAM for the framebuffer is ");
    	SerialPutStr(inttostr((width * (32 / 8) * height)/1024/1024));
    	SerialPutStr(" MB\n");
        
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
    	while(1) {
    		asm ("hlt");
    	}
    }
}
