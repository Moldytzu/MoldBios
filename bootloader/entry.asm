db 0xFF ;Magic boot signature
incbin "c.bin"
times (8*512) - ($-$$) db 0