#pragma once
#define COM1 0x3F8
#include "../IO/ports.h"

void SerialPutStr(char* str);
void SerialPutChar(char ch);
