bits    32
section .text

section .multiboot_header
mbh_start:
    dd 0xE85250D6
    dd 0
    dd mbh_end - mbh_start
    dd 0x100000000 - (0xE85250D6 + 0 + (mbh_end - mbh_start))

    dw 0
    dw 0
    dw 8

mbh_end:
        
global start
extern kmain            ; this function is gonna be located in our c code(kernel.c)
start:
	call kmain
    cli             ;clears the interrupts       ;send processor to continue execution from the kamin funtion in c code
    hlt             ; halt the cpu(pause it from executing from this address
