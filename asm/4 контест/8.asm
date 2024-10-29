;Kirnev Yura 105
extern io_get_udec, io_print_udec
section .data
answer dd 0
sum dd 0
last dd 0
tmp dd 0
n dd 0
k dd 0
section .text
f:
    push ebp
    mov ebp, esp
    mov eax, dword[n]
    mov dword[tmp], eax
    mov dword[sum], 0
    for:
    cmp dword[tmp], 0
    je end
    xor edx, edx
    mov eax, dword[tmp]
    idiv dword[k]
    add dword[sum], edx
    mov dword[tmp], eax
    jmp for
    end:
    mov eax, dword[sum]
    mov esp, ebp
    pop ebp
    ret
    

global main
main:
    call io_get_udec
    mov dword[n], eax
    mov dword[last], eax
    mov dword[answer], eax
    call io_get_udec
    mov dword[k], eax
    
    for2:
    call f
    mov ebx, dword[sum]
    add dword[answer], ebx
    mov eax, dword[sum]
    cmp eax, dword[last]
    je end2
    mov dword[last], eax
    mov dword[n], eax
    jmp for2
    
    end2:
    mov eax, dword[answer]
    call io_print_udec
    xor eax, eax
    re