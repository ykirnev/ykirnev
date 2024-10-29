extern io_get_dec, io_print_dec, io_print_char
section .data
x1 dd 0
x2 dd 0
x3 dd 0
y1 dd 0
y2 dd 0
y3 dd 0
x dd 0
y dd 0
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
    cmp eax, dword[x1]
    je x_exit
    mov dword[x2], eax
    x_exit:
    mov eax, dword[x1]
    cmp eax, dword[x2]
    jl x_exit2
    mov ecx, dword[x2]
    mov dword[x1], ecx
    mov dword[x2], eax
    x_exit2:
    call io_get_dec
    cmp eax, dword[y1]
    je y_exit
    mov dword[y2], eax
    y_exit:
    mov eax, dword[y1]
    cmp eax, dword[y2]
    jl y_exit2
    mov ecx, dword[y2]
    mov dword[y1], ecx
    mov dword[y2], eax
    y_exit2:
    
    call io_get_dec
    call io_get_dec
    call io_get_dec
    cmp eax, dword[x1] 
    jg continue1
    jmp no
    continue1:
    cmp eax, dword[x2]
    jl continue2
    jmp no
    continue2:
    call io_get_dec
    cmp eax, dword[y1] 
    jg continue3
    jmp no
    continue3:
    cmp eax, dword[y2]
    jl continue4
    jmp no
    continue4:
    mov eax, 'Y'
    call io_print_char
    mov eax, 'E'
    call io_print_char
    mov eax, 'S'
    call io_print_char
    jmp end
    no:
    mov eax, 'N'
    call io_print_char
    mov eax, 'O'
    call io_print_char
    end:
    xor eax, eax
    ret