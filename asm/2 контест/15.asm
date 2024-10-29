extern io_print_dec, io_get_dec, io_get_char, io_print_char
section .data
x1 dd 0
x2 dd 0
x3 dd 0
y1 dd 0
y2 dd 0
y3 dd 0

section .text
global main
main:
    mov ebp, esp
    call io_get_dec
    mov dword[x1], eax
    call io_get_dec
    mov dword[y1], eax
    call io_get_dec
    mov dword[x2], eax
    call io_get_dec
    mov dword[y2], eax
    call io_get_dec
    mov dword[x3], eax
    call io_get_dec
    mov dword[y3], eax
    sub eax, dword[y1]
    mov ecx, dword[x2]
    sub ecx, dword[x1]
    imul ecx
    mov dword[x2], eax
    
    mov eax, dword[x3]
    sub eax, dword[x1]
    mov ecx, dword[y2]
    sub ecx, dword[y1]
    imul ecx
    mov ecx, eax
    mov eax, dword[x2]
    sub eax, ecx
    
    mov dword[x1], eax
    sar eax, 31
    mov ecx, eax
    shl ecx, 31
    shr ecx, 31
    xor eax, dword[x1]
    add eax, ecx
    mov dword[x1], eax
    mov edx, eax
    sar edx, 31
    mov ecx, 2
    idiv ecx
    mov dword[x1], edx
    call io_print_dec
    mov eax, '.'
    call io_print_char
    mov edx, dword[x1]
    mov eax, edx
    mov ecx, 5
    imul ecx
    call io_print_dec

    xor eax, eax
    ret