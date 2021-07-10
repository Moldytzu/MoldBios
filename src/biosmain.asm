BITS 32

%include "src/Drivers/serial.asm"
%include "src/Drivers/vga.asm"

;Code
PMEntry:
    mov esi,g_320x200x256
    call VGAWriteRegisters
    
    
    mov [0xB0000],byte 0x1

    mov esi, Branding
    call PutStrS
    jmp $
    
;Data
Branding: db "Moldbios!",10,13,0
