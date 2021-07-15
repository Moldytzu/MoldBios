OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:i386)

SECTIONS {
    . = 0xF0060;
    
    .text : {
        *(.text*)
    }
}
