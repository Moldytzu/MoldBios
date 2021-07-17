#pragma once
#include <stdint.h>
#include "../IO/cmos.h"
#include "ramfb.h"

#define FLOPPY_BASE_PORT 0x3F0

#define FLOPPY_DOR_REG 2
#define FLOPPY_MSR_REG 4
#define FLOPPY_FIFO_REG 5
#define FLOPPY_CCR_REG 7

#define FLOPPY_SPECIFY_COMMAND 3
#define FLOPPY_WRITE_COMMAND 5
#define FLOPPY_READ_COMMAND 6
#define FLOPPY_RECALIBRATE_COMMAND 7
#define FLOPPY_SENSE_COMMAND 8
#define FLOPPY_SEEK_COMMAND 15

#define FLOPPY_DRIVE_MASTER 0
#define FLOPPY_DRIVE_SLAVE 1

uint8_t FloppyGetDrives();
void FloppyDoCommand(uint8_t command);
uint8_t FloppyReadFIFO();
void FloppySenseIntrerrupt(uint8_t* cylinder,uint8_t* status);
void FloppyStartMotor();
void FloppyStopMotor();
void FloppyCalibrate(uint8_t drive);
void FloppyInit(uint8_t drive);
