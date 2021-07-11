#include "Drivers/serial.h"

extern void PMEntry() {
    SerialPutStr("MoldBios!\n\r");
    while(1);
}
