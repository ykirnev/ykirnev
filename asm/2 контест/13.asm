extern io_get_dec, io_print_dec, io_get_char
section .data
xa dd 0
ya dd 0
xb dd 0
yb dd 0
section .text
global main
main:
    mov ebp, esp
    
    call io_get_char
    mov dword[xa], eax
    
    call io_get_char
    mov dword[ya], eax
    call io_get_char
    call io_get_char
    mov dword[xb], eax
    call io_get_char
    mov dword[yb], eax
    mov eax, dword[xa]
    
    sub eax, dword[xb]
    mov dword[xa], eax
    sar eax, 31
    mov ecx, eax
    shl ecx, 31
    shr ecx, 31
    xor eax, dword[xa]
    add eax, ecx
    mov dword[xa], eax
    
    mov eax, dword[ya]
    sub eax, dword[yb]
    mov dword[ya], eax
    sar eax, 31
    mov ecx, eax
    shl ecx, 31
    shr ecx, 31
    xor eax, dword[ya]
    add eax, ecx
    add eax, dword[xa]
    
  
    call io_print_dec
    xor eax, eax
    ret