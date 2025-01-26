; BeeOS bootloader
global start
extern long_mode_start

section .multiboot_header
header_start:
    dd 0xe85250d6                ; multiboot2 magic number
    dd 0                          ; protected mode code
    dd header_end - header_start  ; header length
    
    ; checksum
    dd -(0xe85250d6 + 0 + (header_end - header_start))

    ; end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:

section .text
bits 32
start:
    ; Set up stack
    mov esp, stack_top
    
    ; Multiboot information is in ebx
    mov edi, ebx
    
    ; Call kernel main
    extern kernel_main
    call kernel_main
    
    ; If kernel returns, halt
    cli
.hang:
    hlt
    jmp .hang

section .bss
align 4096
stack_bottom:
    resb 4096 * 4  ; 16KB stack
stack_top:
