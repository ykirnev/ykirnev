;Kirnev Yura 105
extern io_get_udec, io_print_udec
section .data
n dd 0
i dd 0
flag dd 0
last dd 0
section .text
f:
    push ebp
    mov ebp, esp
    mov ebx, 1; deliteli
    mov esi, 0; summa
    mov dword[flag], 0
    forf:
    cmp dword[i], ebx
    je endf
    xor edx, edx
    mov eax, dword[i]
    idiv ebx
    cmp edx, 0
    jne cont
    add esi, ebx
    cont:
    inc ebx
    jmp forf
    endf:
    cmp esi, dword[i]
    jnb end2f
    mov dword[flag], 1
    end2f:
    mov ebp, esp
    pop ebp
    ret
global main
main:
    mov ebp, esp; for correct debugging
    call io_get_udec
    mov dword[n], eax
    mov ecx, 0
    for: 
    inc dword[i]
    cmp ecx, dword[n]
    je end
    call f
    cmp dword[flag], 1
    je addition
    jmp for
    addition:
    inc ecx
    mov ebx, dword[i]
    mov dword[last], ebx
    jmp for
    end:
    mov eax, dword[last]
    call io_print_udec
    xor eax, eax
    ret