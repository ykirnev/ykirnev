;Kirnev Yura 105
extern scanf, printf
section .data
out_format: db '0x%08X',10,0
in_format: db '%u', 0
x dd 0
section .text
global main
main:
    mov ebp, esp
    sub esp, 16
    for:
    mov ebx, in_format
    mov [esp], ebx
    mov ebx, x
    mov [esp + 4], ebx
    call scanf
    cmp eax, 1
    jne end
    mov ebx, out_format
    mov [esp], ebx
    mov ebx, [x]
    mov [esp + 4], ebx
    call printf
    jmp for
    end:
    mov esp, ebp
    xor eax, eax
    ret