#include "floppy.h"

uint8_t FloppyGetDrives() {
	uint8_t drives = CMOSGetRegister(0x10); // Result is in this form: first nibble is the slave floppy type and the second nibble is the master floppy type
	uint8_t master = ((drives >> 4) & 0x0F);
	uint8_t slave =  (drives & 0x0F);
	if(master == 0 && slave == 0)
		return 0;
	else if ((master > 0 && slave == 0) || (master == 0 && slave > 0))
		return 1;
	return 2;
}
