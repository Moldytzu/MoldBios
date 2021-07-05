ASM = nasm
ASMFLAGS = -fbin

INFILES = boot.asm
OUTFILE = bios.qemu

Build:
	$(ASM) $(ASMFLAGS) boot.asm -o bios.qemu
	
Run: Build
	qemu-system-x86_64 -bios bios.qemu -serial stdio
