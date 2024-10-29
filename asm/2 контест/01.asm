extern io_get_dec, io_print_dec, io_print_string
section .data
xv dd 0
yv dd 0
xa dd 0
ya dd 0
t dd 0
answer dd 0
str: db ' '
section .text
global main
main:
    mov ebp, esp
    call io_get_dec
    mov dword[xv], eax
    call io_get_dec
    mov dword[yv], eax
    call io_get_dec
    mov dword[xa], eax
    call io_get_dec
    mov dword[ya], eax
    call io_get_dec
    mov dword[t], eax
    mov eax, dword[t]
    imul dword[xa]
    imul dword[t]
    mov dword[answer], eax
    mov eax, dword[t]
    imul dword[xv]
    add eax, dword[answer]
    call io_print_dec
    mov eax, str
    call io_print_string
    mov eax, dword[t]
    imul dword[ya]
    imul dword[t]
    mov dword[answer], eax
    mov eax, dword[t]
    imul dword[yv]
    add eax, dword[answer]
    call io_print_dec
    
    xor eax, eax
    ret