OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:i386)

SECTIONS {
    . = 0x200101;
    
    .text : {
        *(.text*)
    }
}
