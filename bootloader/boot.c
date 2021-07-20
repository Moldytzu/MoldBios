#include "utils.h"

void BEntry() {
    SerialPutStr("Hello from my bootloader\n\r");
    while(1);
}