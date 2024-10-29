extern io_get_udec, io_print_udec 
section .data
n dd 0
answer dd 1
section .text
global main
main:
    mov ebp, esp
    call io_get_udec
    mov dword[n], eax
    mov ecx, 31999
    for:
    jecxz exit
    dec ecx
    mov eax, dword[n]
    mov edx, eax
    sar edx, 31
    mov ebx, 32000
    sub ebx, ecx
    idiv ebx
    cmp edx, 0
    jne for
    cmp dword[n], ebx
    je exit
    mov dword[answer], eax
    jmp exit
    exit:
    mov eax, dword[answer]
    call io_print_udec
    xor eax, eax
    ret