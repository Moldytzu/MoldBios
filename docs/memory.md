# Memory Layout
### 0x400 to 0x420 is GDT reserved area
### 0x1000 to 0x1400 is Firmware reserved area
### 0x3000 to 0x1400 is Stack reserved area
### 0x3000 to 0xEFFF is Firmware reserved area
### 0xF000 to 0xFFFF is Firmware ROM
### 0x100000 to 0x300000 is Video Framebuffer area
### 0x300000 to 0x301000 is Boot Sector area
### 0x301000 to 0xFFFFFF is Free RAM
###
### If you don't use the firmware functions and you overwrite the stack pointer, you could use the firmware reserved areas 