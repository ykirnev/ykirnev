extern io_get_dec, io_print_dec, io_print_string
section .data
month dd 0
day dd 0
answer dd 0
section .text
global main
main:
    mov ebp, esp
    call io_get_dec
    sub eax, 1
    mov dword[month], eax
    call io_get_dec
    mov dword[day], eax
   
    mov eax, dword[month]
    mov edx, eax
    sar edx, 31
    mov ecx, 2
    idiv ecx 
    mov ecx, 83
    imul ecx
    mov dword[answer], eax
     
    mov eax, dword[month]
    mov edx, eax
    sar edx, 31
    mov ecx, 2
    idiv ecx
    mov eax, edx
    mov ecx, 41
    imul ecx
    add dword[answer], eax
    mov eax, dword[answer]
    add eax, dword[day]
    call io_print_dec
    xor eax, eax
    ret