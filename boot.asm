COM1: equ 0x3F8

BITS 16

ORG 0xF0000 ;bios block location

;Code

boot:
    call initsegments

    ;print the boot text
    mov si,Info
    call putstr
    mov si,BootText
    call putstr
    mov si,NewLine
    call putstr
    
    ;todo: load gdt
    
    ;enable protection in cr0
    mov eax,cr0
    or eax,1
    mov cr0,eax
    
    ;todo: load segment selectors
    
    ;todo: jump into protected mode
    
    jmp $    

;InitSegments
;
;Inits the segments
;
initsegments:
    mov ax, cs
    mov ds, ax
    mov ax, 0
    mov es, ax
    ret
    
;PutChar
;
;Put a char onto the debugcon
;
;Input: AL=char
;Output: none
;
putchar:
    mov dx,COM1
    out dx,al ;plot char on the serial console
    ret

;PutStr
;
;Put a string onto the debugcon
;
;Input: SI=string pointer
;Output: none
;
putstr:
.loop:
    lodsb ;load byte from string
    cmp al,0 ;check for null
    je .done ;if it's null exit
    call putchar ;print the char
    jmp .loop ;loop
.done:
    ret ;return

;Data    

Info: db "INFO: ",0
BootText: db "MoldBios started in Real Mode!",0   
NewLine: db 10,13,0

;Reset vector
times (0x10000 - 16) - ($ - $$) db 0x00

ResetVector:
    cli ;disable intrerupts
    cld ;clear directional flag
    jmp 0xF000:0
    times 9 db 0
