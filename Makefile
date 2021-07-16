rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
reverse=$(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1)))) $(firstword $(1))

ASM = nasm
ASMFLAGS = -fbin

CC = gcc
CFLAGS = -m32 -ffreestanding -fno-pic -w #note to self: don't add compiler optimizations ever again

LD = ld
LDFLAGS = -nostdlib -static -T link.ld

SRCDIR := src
OBJDIR := bin/obj

SRC = $(call rwildcard,$(SRCDIR),*.c)
OBJS = $(call reverse,$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC)))
DIRS = $(wildcard $(SRCDIR)/*)

OUTFILE = bin/bios.qemu

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

Link: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o bin/obj/c.bin

Build: Clean Link
	@ stat -L -c "[Notice] Size of C blob is %s B / 65535 B" bin/obj/c.bin 
	$(ASM) $(ASMFLAGS) src/boot.asm -o $(OUTFILE)
	
Clean:
	rm -rf bin

Run: Build
	qemu-system-x86_64 -bios $(OUTFILE) -serial stdio -vga none -device ramfb -m 2G

