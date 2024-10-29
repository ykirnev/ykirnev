extern io_get_dec, io_print_dec, io_get_char
section .data
answer dd 0
section .text
global main
main:
    mov ebp, esp
    
    call io_get_char
    mov ecx, 'A'
    sub eax, ecx
    mov ecx, 7
    sub ecx, eax
    mov dword[answer], ecx
    call io_get_char
    mov ecx, '1'
    sub eax, ecx
    mov ecx, 7
    sub ecx, eax
    mov eax, dword[answer]   
    imul ecx
    mov edx, eax
    sar edx, 31
    mov ecx, 2
    idiv ecx
    call io_print_dec
    xor eax, eax
    ret