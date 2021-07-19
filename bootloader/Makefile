CC = gcc
CFLAGS = -m32 -ffreestanding -fno-pic -w -Os

LD = ld
LDFLAGS = -nostdlib -static -T link.ld

SRCDIR := src
OBJDIR := bin/obj

SRC = boot.c
OBJS = boot.o
DIRS = 

OUTFILE = bloader.bin

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

Link: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(OUTFILE)

Build: Clean Link
	
Clean:
	rm -rf bin