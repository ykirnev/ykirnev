extern io_get_udec, io_print_udec
section .text
global main
main:
    mov ebp, esp
    call io_get_udec
    mov ebx, eax
    xor eax, eax
    mov ecx, 32
    for:
    jecxz exit
    dec ecx
    shl ebx, 1
    jb addition
    jmp for
    addition:
    inc eax
    jmp for
    exit:
    call io_print_udec
    xor eax, eax
    ret