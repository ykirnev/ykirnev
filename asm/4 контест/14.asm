;Kirnev Yura 105
extern io_get_udec, io_print_udec
section .data
i dd 0
k dd 0
n dd 0
a dd 0
x0 dd 0
x1 dd 0
xnew dd 0
contret dd 0
contleft dd 0
contright dd 0
size_right dd 0
section .text
cont:
    mov ebp, esp; for correct debugging
    mov dword[size_right], 0
    mov ecx, dword[k]
    mov eax, dword[contright]
    cmp eax, 0
    jne for_size_right
    mov dword[size_right], 1
    jmp end_for_size_right
    for_size_right:
    cmp eax, 0
    je end_for_size_right
    xor edx, edx
    idiv ecx
    inc dword[size_right]
    jmp for_size_right
    end_for_size_right:
    mov eax, dword[contleft]
    for_umn:
    cmp dword[size_right], 0
    je end_umn
    dec dword[size_right]
    imul eax, ecx
    jmp for_umn
    end_umn:
    add eax, dword[contright]
    mov dword[contret], eax
    mov ebp, esp
  
    ret
global main
main:
    mov ebp, esp
    call io_get_udec
    mov dword[k], eax
    call io_get_udec
    mov dword[n], eax
    call io_get_udec
    mov dword[a], eax
    xor edx, edx
    mov ebx, 2011
    idiv ebx
    mov dword[x0], edx
    mov dword[contleft], edx
    mov dword[contright], edx
    call cont
    mov eax, dword[contret]
    xor edx, edx
    idiv ebx
    mov dword[x1], edx
    mov dword[xnew], edx
    cmp dword[n], 1
    je end
    mov dword[i], 1
    for:
    mov ecx, dword[i]
    cmp ecx, dword[n]
    je end
    mov eax, dword[x0]
    mov dword[contright], eax
    mov eax, dword[x1]
    mov dword[contleft], eax
    call cont
    mov eax, dword[contret]
    xor edx, edx
    mov ebx, 2011
    idiv ebx
    mov ebx, dword[x1]
    mov dword[x0], ebx
    mov dword[x1], edx
    mov dword[xnew], edx
    inc dword[i]
    jmp for
    end:
    mov eax, dword[xnew]
    call io_print_udec
    xor eax, eax
    ret