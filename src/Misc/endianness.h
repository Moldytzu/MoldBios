#pragma once
#include <stdint.h>
//This is for endiannes correction I will need

static inline uint8_t swapendianness8(uint8_t byte) {
    return (byte >> 4) | (byte << 4); //https://stackoverflow.com/questions/1192487/swap-bits-in-a-number-in-c
}

static inline uint16_t swapendianness16(uint16_t byte) {
    return (byte >> 8) | (byte << 8); 
}

static inline uint32_t swapendianness32(uint32_t byte) {
    return ((byte >> 8) & 0x0000FF00) | ((byte >> 24) & 0x000000FF) |((byte << 24) & 0xFF000000) | ((byte << 8) & 0x00FF0000);  //we need those ands to be sure we select the bits correctly
}

static inline uint64_t swapendianness64(uint64_t byte) {
    return (uint64_t)(swapendianness32((byte >> 32)&0xFFFFFFFF) | (swapendianness32(byte &0xFFFFFFFF)<<32)); //we need to bitshift the high byte because swapendianness32 will give us low byte values so we need to move them to the higher part
}