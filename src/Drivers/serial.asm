COM1 equ 0x3F8
COM2 equ 0x2F8
COM3 equ 0x3E8
COM4 equ 0x2E8

;PutCharS
;
;Put a char onto the serial console
;
;Input: AL=char
;Output: none
;
PutCharS:
    mov dx,COM1
    out dx,al ;plot char on the serial console
    ret

;PutStrS
;
;Put a string onto the serial console
;
;Input: ESI=string pointer
;Output: none
;
PutStrS:
.loop:
    lodsb ;load byte from string
    cmp al,0 ;check for null
    je .done ;if it's null exit
    call PutCharS ;print the char
    jmp .loop ;loop
.done:
    ret ;return
    
;ClearSerialConsole
;
;Clears the serial console
;
ClearSerialConsole:
    mov esi,ClearScreenSequence
    call PutStrS
    ret
    
ClearScreenSequence: db 27,"[2J",27,"[H",0
