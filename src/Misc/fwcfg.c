#include "fwcfg.h"

//I hate endianness

void FWCFGWrite(uint16_t selector, void* buffer, uint32_t lenght, uint32_t offset) {
    volatile struct FWCFG_DMA DMA;

    DMA.Address = 0;
    DMA.Length = swapendianness32(offset);
    DMA.Control = swapendianness32(((uint32_t) selector << 16) | CONTROL_SKIP | CONTROL_SELECT); //we're selecting the control signal
    outd(FWCFG_DMA_PORT + 4,swapendianness32(&DMA)); //sending the address of the DMA struct so it can select the selector

    while (DMA.Control & ~CONTROL_ERROR); //wait until is done

    DMA.Address = swapendianness64(buffer);
    DMA.Length = swapendianness32(lenght);
    DMA.Control = swapendianness32(((uint32_t) selector << 16) | CONTROL_WRITE); //we're selecting the write signal
    outd(FWCFG_DMA_PORT + 4,swapendianness32(&DMA)); //sending the address of the DMA struct so it can write the buffer

    while (DMA.Control & ~CONTROL_ERROR); //wait until is done
}