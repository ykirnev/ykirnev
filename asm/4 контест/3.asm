extern io_get_dec, io_print_dec, io_print_char
section .text
f:
    push ebp
    mov ebp, esp
    sub esp, 4
    call io_get_dec
    mov dword[esp], eax
    cmp dword[esp], 0
    je exit
    call f
    mov eax, dword[esp]
    call io_print_dec
    mov eax, ' '   
    call io_print_char
    exit:
    mov esp, ebp
    pop ebp
    ret
    
global main
main:
    mov ebp, esp; for correct debugging
    call f
    xor eax, eax
    ret