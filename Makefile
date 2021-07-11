ASM = nasm
ASMFLAGS = -fbin

CC = gcc
CFLAGS = -m32 -ffreestanding -static -fno-pic -fno-stack-protector -w -O0

LD = ld
LDFLAGS = -nostdlib -static -Tlink.ld

OUTFILE = bin/bios.qemu

Build:
	$(CC) $(CFLAGS) -c src/protectedmode.c -o bin/obj/protectedmode.o
	$(CC) $(CFLAGS) -c src/Drivers/serial.c -o bin/obj/Drivers/serial.o
	$(CC) $(CFLAGS) -c src/Drivers/vga.c -o bin/obj/Drivers/vga.o
	$(LD) $(LDFLAGS) bin/obj/protectedmode.o bin/obj/Drivers/serial.o bin/obj/Drivers/vga.o -o bin/obj/c.bin
	$(ASM) $(ASMFLAGS) src/boot.asm -o $(OUTFILE)
	
Run: Build
	qemu-system-x86_64 -bios $(OUTFILE) -serial stdio
