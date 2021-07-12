#include "fwcfg.h"

//I hate endianness

void FWCFGDMATransfer(void* buffer, uint32_t len, uint32_t control) {
    struct FWCFG_DMA dma;

    if(!len) return; //we return if the len is 0

    dma.Address = swapendianness64(buffer);
    dma.Length = swapendianness32(len);
    dma.Control = swapendianness32(control);

}

int FWCFGLocateFile(const char* file) {

}