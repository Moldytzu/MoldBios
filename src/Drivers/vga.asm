miscPort equ 0x3C2
crtcIndexPort equ 0x3D4
crtcDataPort equ 0x3D5
sequencerIndexPort equ 0x3C4
sequencerDataPort equ 0x3C5
graphicsControllerIndexPort equ 0x3CE
graphicsControllerDataPort equ 0x3CF
attributeControllerWritePort equ 0x3C0
attributeControllerReadPort equ 0x3C1
attributeControllerIndexPort equ 0x3C0
attributeControllerResetPort equ 0x3DA

;VGAWriteRegisters
;
;Write VGA registers
;
;Input: esi=registers
;Output: none
;
VGAWriteRegisters:
    ;misc
    lodsb
    mov dx,miscPort 
    out dx,al
    
    ;sequencer
    mov cx,4
.l1:
    mov al,cl
    mov dx,sequencerIndexPort 
    out dx,al
    lodsb
    mov dx,sequencerDataPort 
    out dx,al
    dec cx
    loop .l1
    
    ;crt controller
    mov al,3
    mov dx,crtcIndexPort
    out dx,al ;write 3
    
    in al,crtcDataPort
    or al, 0x80 ; crtcDataPort.Read | 0x80
    
    mov dx,crtcDataPort
    out dx,al ;write al
    
    mov al,0x11
    mov dx,crtcIndexPort
    out dx,al

    in al,crtcDataPort
    and al, 0x7F
    
    mov dx,crtcDataPort
    out dx,al
  
    mov cx,24
.l2:
    mov al,cl
    mov dx,crtcIndexPort 
    out dx,al
    lodsb
    mov dx,crtcDataPort 
    out dx,al
    dec cx
    loop .l2
    
    ;graphics controller
    mov cx,8
.l3:
    mov al,cl
    mov dx,graphicsControllerIndexPort 
    out dx,al
    lodsb
    mov dx,graphicsControllerDataPort 
    out dx,al
    dec cx
    loop .l3
  
    ;attribute controller
    mov cx,20
.l4:
    in al,attributeControllerResetPort
    mov al,cl
    mov dx,attributeControllerWritePort 
    out dx,al
    lodsb
    mov dx,attributeControllerWritePort 
    out dx,al
    dec cx
    loop .l4
  
    in al,attributeControllerResetPort
    mov al,0x20
    mov dx, attributeControllerWritePort
    out dx,al
  
    ret
    
;Modes
g_320x200x256: db 0x63,0x03,0x01,0x8F,0x00,0x0E,0x5F,0x4F,0x50,0x82,0x54,0x80,0xBF,0x1F,0x00,0x41,0x00,0x7F,0x00,0x00,0x00,0x00,0x9C,0x0E,0x8F,0x28,0x40,0x96,0xB9,0xA3,0xFF,0x00,0x00,0x00,0x00,0x00,0x40,0x05,0x0F,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x41,0x00,0x0F,0x00,0x00
