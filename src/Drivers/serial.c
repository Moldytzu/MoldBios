#include "serial.h"

void SerialPutStr(char* str) {
    for(int i = 0; str[i] != '\0';i++) {
    	if(str[i] == '\n')
    		SerialPutChar('\r');
        SerialPutChar(str[i]);    
    }
}

void SerialPutChar(char ch) {
    outb(COM1, ch);
}
