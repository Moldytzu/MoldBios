ASM = nasm
ASMFLAGS = -fbin

CC = gcc
CFLAGS = -m32 -ffreestanding -static -fno-pic -fno-stack-protector -std=gnu99 -w -O0

LD = ld
LDFLAGS = -nostdlib -static -Tlink.ld

OUTFILE = bin/bios.qemu

CBuild:
	mkdir -p bin/obj/IO/
	mkdir -p bin/obj/Drivers/

	$(CC) $(CFLAGS) -c src/protectedmode.c -o bin/obj/protectedmode.o
	$(CC) $(CFLAGS) -c src/Drivers/serial.c -o bin/obj/Drivers/serial.o
	$(CC) $(CFLAGS) -c src/Drivers/pci.c -o bin/obj/Drivers/pci.o

Build: CBuild
	$(LD) $(LDFLAGS) bin/obj/protectedmode.o bin/obj/Drivers/serial.o bin/obj/Drivers/pci.o -o bin/obj/c.bin
	$(ASM) $(ASMFLAGS) src/boot.asm -o $(OUTFILE)
	
Run: Build
	qemu-system-x86_64 -bios $(OUTFILE) -serial stdio -vga std -global VGA.vgamem_mb=32 -machine q35
