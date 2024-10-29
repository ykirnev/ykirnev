;Kirnev Yura 105 5_14 vers 3.0
extern scanf, fprintf, get_stdout, fclose
section .data
in_format: db "%d", 10, 0
mas times 10000 dd 0
n dd 0
x dd 0
i dd 0
section .text
apply:
    push ebp
    mov ebp, esp
    
    mov eax, [ebp + 20]
    inc eax
    imul edx, eax, 4
    sub esp, edx
    
    mov esi, 0
    for_apply:
        cmp esi, [n]
        je end_for_apply
        mov eax, [ebp + 24]
        mov [esp], eax
        mov eax, [ebp + 28]
        mov [esp + 4], eax
        mov eax, [mas + esi * 4]
        mov [esp + 8], eax
        call [ebp + 16]
        inc esi
        jmp for_apply
    
    end_for_apply:
    leave
    ret
    
global main
main:
    mov ebp, esp
    sub esp, 32
    
    mov eax, in_format
    mov [esp], eax
    mov eax, n
    mov [esp + 4], eax
    call scanf
   
    mov esi, 0
    for:
        cmp esi, dword[n]
        je end_for
        mov eax, in_format
        mov [esp], eax
        mov eax, x
        mov [esp + 4], eax
        call scanf
        mov eax, [x]
        mov [mas + esi * 4], eax
        inc esi
        jmp for
        
    end_for: 
    call get_stdout  
    mov ebx, eax
    mov eax, mas
    mov [esp], eax
    mov eax, [n]
    mov [esp + 4], eax
    mov eax, fprintf
    mov [esp + 8], eax
    mov eax, 2
    mov [esp + 12], eax
    mov [esp + 16], ebx
    mov eax, in_format
    mov [esp + 20], eax
    call apply
    
    mov [esp], ebx
    call fclose
      
    mov esp, ebp
    xor eax, eax
    ret