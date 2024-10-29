;Kirnev Yura 105
extern io_get_udec, io_print_udec
section .data
number dd 0
n dd 0
k dd 0
flag dd 0
sum_number dd 0
sum_right dd 0
size_number dd 0
section .text
check_hapiness:
    push ebp
    mov ebp, esp
     mov dword[flag], 0
    mov dword[sum_number], 0
    mov dword[sum_right], 0
    mov dword[size_number], 0
    mov eax, dword[n]
    mov ebx, dword[k]
    for_size_number:
    cmp eax, 0
    je end_for_size_number
    xor edx, edx
    idiv ebx
    add dword[sum_number], edx
    inc dword[size_number]
    jmp for_size_number
    end_for_size_number:
    inc dword[size_number]
    xor edx, edx
    mov ebx, 2
    mov eax, dword[size_number]
    idiv ebx
    mov ecx, eax
    mov eax, dword[n]
    mov ebx, dword[k]
    for2:
    cmp ecx, 0
    je end_for2
    xor edx, edx
    idiv ebx
    add dword[sum_right], edx
    dec ecx
    jmp for2
    end_for2:
    mov eax, dword[sum_number]
    sub eax, dword[sum_right]
    cmp eax, dword[sum_right]
    jne NO
    mov dword[flag], 1
    NO:
    mov ebp, esp
    pop ebp
    ret
    
global main
main:
    call io_get_udec
    mov dword[n], eax
    call io_get_udec
    mov dword[k], eax
    for:
    cmp dword[flag], 1
    je end
    call check_hapiness
    inc dword[n]
    jmp for
    end:
    mov eax, dword[n]
    dec eax
    call io_print_udec
    xor eax, eax
    ret