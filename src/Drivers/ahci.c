#include "ahci.h"

uint8_t AHCIDetectController() {
	return PCIFindDevice(0x1, 0x6, 0x1);
}
