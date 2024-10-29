Kirnev Yura 105
extern io_get_udec, io_print_char
section .data
n dd 0
sum dd 0
i dd 0
section .text
div3:
    push ebp
    mov ebp, esp
    mov dword[sum], 0
    for:
    cmp dword[n], 0
    je end
    xor edx, edx
    mov eax, dword[n]
    mov ebx, 10
    idiv ebx
    add dword[sum], edx
    mov dword[n], eax
    jmp for
    end:
    mov eax, dword[sum]
    xor edx, edx
    mov ebx, 3
    idiv ebx
    cmp edx, 0
    je YES
    mov eax, 'N'
    call io_print_char
    mov eax, 'O'
    call io_print_char
    mov eax, 0x0A
    call io_print_char
    jmp final
    YES:
    mov eax, 'Y'
    call io_print_char
    mov eax, 'E'
    call io_print_char
    mov eax, 'S'
    call io_print_char
    mov eax, 0x0A
    call io_print_char
    final:
    mov esp, ebp
    pop ebp
    ret

global main
main:
    mov ebp, esp; for correct debugging
    call io_get_udec
    mov dword[i], eax
    form:
    cmp dword[i], 0
    je exitm
    dec dword[i]
    call io_get_udec
    mov dword[n], eax
    call div3
    jmp form
    exitm:
    xor eax, eax
    ret