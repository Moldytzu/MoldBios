OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:i386)
ENTRY(BEntry)

SECTIONS {
    . = 0x300000;
    
    .data : {
        *(.data*)
    }

    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .bss : {
        *(.bss*)
    }

}
