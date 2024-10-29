 Yura 105
extern scanf, strcmp, printf, malloc, qsort
section .data
    int_format: db "%d", 0
    lines_format: db "%s", 0
    mas times 5500 db 0
    s times 11 db 0
    n dd 0
    i dd 0
    cnt dd 0
section .text
global main
main:
    mov ebp, esp
    
    sub esp, 16
    mov eax, int_format
    mov [esp], eax
    mov eax, n
    mov [esp + 4], eax
    call scanf
    
for: 
    mov eax, dword[i]
         
    cmp dword[n], eax
    je end_for    
   
    mov eax, lines_format
    mov [esp], eax
    mov edx, dword[i]
    imul ecx, edx, 11
    lea eax, [mas + ecx]
    mov [esp + 4], eax
    call scanf     
    inc dword[i] 
    jmp for
    
end_for:
    
    mov eax, mas
    mov [esp], eax
    mov eax, dword[n]
    mov [esp + 4], eax
    mov dword[esp + 8], 11
    mov eax, strcmp
    mov [esp + 12], eax
    call qsort
    
    mov dword[i], 0
    
second_for:
    mov ecx, dword[i]
    cmp ecx, dword[n]
    je end_end
    imul ecx, 11
    lea eax, [mas + ecx]
    mov [esp], eax
    sub eax, 11
    mov [esp + 4], eax
    call strcmp
    inc dword[i]
    cmp eax, 0
    je second_for
    inc dword[cnt]  
    jmp second_for    
    
end_end:   
    mov eax, int_format
    mov [esp], eax
    mov eax, [cnt]
    mov [esp + 4], eax
    call printf
    
    mov esp, ebp
    xor eax, eax
    ret