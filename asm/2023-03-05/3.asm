extern io_get_dec, io_print_dec, io_print_string
section .data
a dd 0
b dd 0
c dd 0
d dd 0
e dd 0
f dd 0
answer dd 0
section .text
global main
main:
    mov ebp, esp
    call io_get_dec
    mov dword[a], eax
    call io_get_dec
    mov dword[b], eax
    call io_get_dec
    mov dword[c], eax
    call io_get_dec
    mov dword[d], eax
    call io_get_dec
    mov dword[e], eax
    call io_get_dec
    mov dword[f], eax
    
    mov eax, dword[e]
    add eax, dword[f]
    imul dword[a]
    add dword[answer], eax
    

    mov eax, dword[d]
    add eax, dword[f]
    imul dword[b]
    add dword[answer], eax
    
    mov eax, dword[d]
    add eax, dword[e]
    imul dword[c]
    add dword[answer], eax
        
    mov eax, dword[answer]
    call io_print_dec
    
    xor eax, eax
    ret