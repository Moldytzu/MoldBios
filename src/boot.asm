BITS 16

ORG 0xF0000 ;bios block location

;Code

boot:
    ;Init 16-bit segments
    call InitSegments
    
    ;Copy the GDT outisde ROM mapped memory
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

    ;Set up the 32-bit segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x2000

    ;Jump
    jmp dword 0x08:PMEntry

;InitSegments
;
;Inits the segments
;
InitSegments:
    mov ax, cs
    mov ds, ax
    mov ax, 0
    mov es, ax
    ret

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

%include "src/biosmain.asm"
    
BITS 16
;Reset vector
times (0x10000 - 16) - ($ - $$) db 0x00

ResetVector:
    cli ;disable intrerupts
    cld ;clear directional flag
    jmp 0xF000:0
    times 9 db 0
