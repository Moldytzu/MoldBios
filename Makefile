ASM = nasm
ASMFLAGS = -fbin

OUTFILE = bin/bios.qemu

Build:
	$(ASM) $(ASMFLAGS) src/boot.asm -o $(OUTFILE)
	
Run: Build
	qemu-system-x86_64 -bios $(OUTFILE) -serial stdio
