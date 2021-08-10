BITS 16

ORG 0xF0000 ;bios block location

;Code

boot:
    ;Init 16-bit segments
    mov ax, cs
    mov ds, ax
    xor ax, ax ;save some bytes
    mov es, ax
    
    ;Copy the GDT outisde ROM mapped memory (taken from AtieP's bios)
    mov si, GDT
    mov di, 0x400
    mov cx, GDTEnd - GDT
    rep movsb

    ;Load the GDT
    lgdt [GDTDescriptor]

    ;Enable Protection in CR0
    mov eax, cr0
    or al, 1
    mov cr0, eax

    ;Set up the 32-bit segments (also taken from AtieP's bios)
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x20000

    ;Jump
    jmp dword 0x08:CBin

;Data
    
;Global Descriptor Table
GDT:
    dq 0x0000000000000000
    dq 0x00cf9a000000ffff
    dq 0x00cf93000000ffff
    
GDTEnd:

GDTDescriptor:
    dw GDTEnd - GDT - 1
    dd 0x400

times 0x60 - ($ - $$) db 0x00

CBin:
incbin "bin/obj/c.bin"
    
BITS 16
;Reset vector
times (0x10000 - 16) - ($ - $$) db 0x00

ResetVector:
    cli ;disable intrerupts
    cld ;clear directional flag
    jmp 0xF000:boot
    times 0x10000 - ($ - $$) db 0x00
