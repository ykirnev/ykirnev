extern io_get_udec, io_print_udec 
section .data
a dd 0
b dd 0
tmp dd 0
answer dd 1
section .text
global main
main:
    mov ebp, esp
    call io_get_udec
    mov dword[a], eax
    call io_get_udec
    mov dword[b], eax
    cmp eax, dword[a]
    ja after
    mov ecx, dword[a]
    mov dword[b], ecx
    mov dword[a], eax
    after:
    mov ecx, 10000000
    for:
    jecxz exit
    dec ecx
    mov eax, dword[a]
    mov edx, eax
    sar edx, 31
    mov ebx, 10000000
    sub ebx, ecx
    idiv ebx
    cmp edx, 0
    jne for
    mov ebx, eax
    mov eax, dword[b]
    mov edx, eax
    sar edx, 31
    idiv ebx
    cmp edx, 0
    jne for
    mov dword[answer], ebx
    jmp exit
    exit:
    mov eax, dword[answer]
    call io_print_udec
    xor eax, eax
    ret