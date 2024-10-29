;Kirnev Yura 105
extern fopen, fscanf, fprintf, fclose, qsort
section .data
out_format: db "%d", 10, 0
in_format: db "%d", 0
in_fopen_name: db "input.txt", 0
in_fopen_type: db "r", 0
out_fopen_name: db "output.txt", 0
out_fopen_type: db "w", 0
a dd 0
b dd 0
x dd 0
cnt dd 0
len dd 0
FILE dd 0
mas times 1000 dd 0
section .text
comp:
    push ebp
    mov ebp, esp
    mov ecx, [ebp + 8]
    mov eax, [ecx]
    mov ecx, [ebp + 12]
    mov edx, [ecx]
    cmp eax, edx
    jne cont1
    mov eax, 0
    mov esp, ebp
    pop ebp
    ret
    cont1:
    cmp eax, edx
    jl cont2
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret
    cont2:
    mov eax, -1
    mov esp, ebp
    pop ebp
    ret

global main
main:
    mov ebp, esp
    sub esp, 32
    mov ebx, in_fopen_name
    mov [esp], ebx
    mov ebx, in_fopen_type
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
    cmp eax, -1
    je sort
    mov eax, dword[x]
    mov ecx, dword[cnt]
    mov dword[mas + ecx * 4], eax
    inc dword[cnt]
    jmp for
    sort:
    mov ebx, dword[FILE]
    mov [esp], ebx
    call fclose
    mov eax, mas
    mov [esp], eax
    mov ecx, dword[cnt]
    mov [esp + 4], ecx
    mov dword[esp + 8], 4
    mov ebx, comp
    mov dword[esp + 12], ebx
    call qsort
    end:
    mov ebx, out_fopen_name
    mov [esp], ebx
    mov ebx, out_fopen_type
    mov [esp + 4], ebx
    call fopen
    mov dword[FILE], eax
    mov [esp], eax
    mov ebx, dword[cnt]
    mov dword[len], ebx
    
    for_end:
    mov ecx, dword[cnt]
    cmp ecx, 0
    je final
    mov ebx, out_format
    mov [esp + 4], ebx
    neg ecx
    add ecx, dword[len]
    mov ebx, [mas + ecx * 4]
    mov [esp + 8], ebx
    call fprintf
    dec dword[cnt]
    jmp for_end
   
    final:
    mov ebx, dword[FILE]
    mov [esp], ebx
    call fclose
    mov esp, ebp
    xor eax, eax
    rets