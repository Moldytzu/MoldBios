OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:i386)

SECTIONS {
    . = 0x300000;
    
    .text : {
        *(.text*)
    }

    .data : {
        *(.data*)
    }

    .rodata : {
        *(.rodata*)
    }

    .bss : {
        *(.bss*)
    }

}
