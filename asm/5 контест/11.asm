;Kirnev Yura 105
extern fprintf, fopen, fclose, fscanf, io_print_dec
section .data
out_format: db "%d", 10, 0
in_format: db "%d", 0
in_fopen_name: db "input.txt", 0
in_fopen_type: db "r", 0
out_fopen_name: db "output.txt", 0
out_fopen_type: db "w", 0
end_output: db "1", 0
mas times 1200000 dd 0
FILE dd 0
n dd 0
m dd 0
i dd 0
root dd 0
left dd 0
right dd 0
left_left dd 0
right_right dd 0
section .text
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
    
    mov ebx, [FILE]
    mov [esp], ebx
    mov ebx, in_format
    mov [esp + 4], ebx
    mov ebx, n
    mov [esp + 8], ebx
    call fscanf
    
    mov eax, dword[n]
    cmp eax, 1
    je end_1
    
    mov ebx, [FILE]
    mov [esp], ebx
    mov ebx, in_format
    mov [esp + 4], ebx
    mov ebx, m
    mov [esp + 8], ebx
    call fscanf
    
    
init:   
    mov eax, 1
    mov [mas], eax
    lea eax, [mas + 12]
    mov [mas + 4], eax
    mov eax, mas
    mov dword[root], eax
    inc dword[i]
    
for_init:
    mov ecx, dword[i]
    cmp dword[n], ecx
    je end_init
    imul ebx, ecx, 12
    inc ecx
    mov [mas + ebx], ecx
    mov eax, mas
    add eax, ebx
    add eax, 12
    mov [mas + ebx + 4], eax
    sub eax, 24
    mov [mas + ebx + 8], eax
    inc dword[i]
    jmp for_init
    
end_init:
    mov eax, 0
    mov[mas + ebx + 4], eax
    mov dword[i], 0
    

for_asks:
    mov ecx, dword[i]
    cmp ecx, dword[m]
    je end_asks
    
    inc dword[i]
    
    mov ebx, [FILE]
    mov [esp], ebx
    mov ebx, in_format
    mov [esp + 4], ebx
    mov ebx, left
    mov [esp + 8], ebx
    call fscanf
    
    mov ebx, [FILE]
    mov [esp], ebx
    mov ebx, in_format
    mov [esp + 4], ebx
    mov ebx, right
    mov [esp + 8], ebx
    call fscanf
    
    mov esi, [left]
    sub esi, 1
    imul esi, 12
    mov eax, mas
    add eax, esi
    mov [left], eax
    add eax, 8
    mov eax, [eax]
    mov [left_left], eax
    
    mov esi, [right]
    sub esi, 1
    imul esi, 12
    mov eax, mas
    add eax, esi
    mov [right], eax
    add eax, 4
    mov eax, [eax]
    mov [right_right], eax
    
    cmp dword[left_left], 0
    je for_asks
    
    cmp dword[right_right], 0
    je changes0
        changes:
        mov esi, dword[left]
        add esi, 8 
        mov dword[esi], 0
        
        mov eax, [right_right]
        mov esi, dword[left_left]
        add esi, 4
        mov dword[esi], eax
        

        mov eax, [left_left]
        mov esi, dword[right_right]
        add esi, 8 
        mov dword[esi], eax
   
        mov eax, [root]
        mov esi, [right]
        add esi, 4
        mov dword[esi], eax
        
        mov eax, [right]
        mov esi, dword[root]
        add esi, 8
        mov [esi], eax
        
        mov eax, [left]
        mov esi, dword root
        mov[esi], eax

        jmp for_asks
     changes0:
        mov esi, dword[left]
        add esi, 8 
        mov dword[esi], 0
        
        mov esi, dword[left_left]
        add esi, 4
        mov dword[esi], 0
        
        mov eax, [root]
        mov esi, [right]
        add esi, 4
        mov dword[esi], eax
        
        mov eax, [right]
        mov esi, dword[root]
        add esi, 8
        mov [esi], eax
        
        mov eax, [left]
        mov esi, dword root
        mov[esi], eax
        
         jmp for_asks
        
end_asks:
    mov ebx, dword[FILE]
    mov [esp], ebx
    call fclose

    mov ebx, out_fopen_name
    mov [esp], ebx
    mov ebx, out_fopen_type
    mov [esp + 4], ebx
    call fopen
    mov dword[FILE], eax
    mov dword[i], 0
    
print_for:
    mov ecx, dword[i]
    cmp ecx, dword[n]
    je end
    inc dword[i]
    mov eax, dword[FILE]
    mov [esp], eax
    mov eax, out_format
    mov [esp + 4], eax
    mov esi, dword[root]
    mov eax, [esi]
    mov [esp + 8], eax
    call fprintf
    add esi, 4
    mov esi, [esi]
    mov dword[root], esi
    jmp print_for
    
end:
    mov ebx, dword[FILE]
    mov [esp], ebx
    call fclose
    mov esp, ebp
    xor eax, eax
    ret
   
end_1:
    mov ebx, dword[FILE]
    mov [esp], ebx
    call fclose

    mov ebx, out_fopen_name
    mov [esp], ebx
    mov ebx, out_fopen_type
    mov [esp + 4], ebx
    call fopen
    mov dword[FILE], eax
    
    mov eax, dword[FILE]
    mov [esp], eax
    mov eax, end_output
    mov [esp + 4], eax
    call fprintf
    
    mov ebx, dword[FILE]
    mov [esp], ebx
    call fclose
    mov esp, ebp
    xor eax, eax
    ret
    
    