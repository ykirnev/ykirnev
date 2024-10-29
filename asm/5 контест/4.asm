;Kirnev Yura 105
extern fopen, fscanf, printf
section .data
in_format: db "%u", 0
fopen_name: db "data.in", 0
fopen_type: db "r", 0
x dd 0
cnt dd 0
FILE dd 0
section .text
global main
main:
    mov ebp, esp
    sub esp, 16
    mov ebx, fopen_name
    mov [esp], ebx
    mov ebx, fopen_type
    mov [esp + 4], ebx
    call fopen
    mov dword[FILE], eax
    for:
    mov ebx, [FILE]
    mov [esp], ebx
    mov ebx, in_format
    mov [esp + 4], ebx
    mov ebx, x
    mov [esp + 8], ebx
    call fscanf
    cmp eax, 1
    jne end
    inc dword[cnt]
    jmp for
    end:
    mov eax, dword[cnt]
    mov ebx, in_format
    mov [esp], ebx
    mov ebx, dword[cnt]
    mov [esp + 4], ebx
    call printf
    mov esp, ebp
    xor eax, eax
    ret