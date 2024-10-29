;Kirnev Yura 105 group
extern io_get_udec, io_print_udec
section .data
n dd 0
n_copy dd 0
k_copy dd 0
r_sum dd 0
m dd 0
k dd 0
r_prev dd 0
Cnk dd 1
answer dd 0
section .text
global main
main:
    mov ebp, esp; for correct debugging
    call io_get_udec
    mov dword[n], eax
    mov dword[n_copy], eax
    call io_get_udec
    mov dword[k], eax
    mov dword[k_copy], eax
    
    
    cmp eax, 0
    jne GO
    
    qqq:
    bsr ecx, dword[n]
    add ecx, 1
    mov eax, 1
    shl eax, cl
    sub eax, 1
    cmp eax, dword[n]
    jne qwerty
    mov dword[answer], ecx
    jmp output
    qwerty:
    sub ecx, 1
    mov dword[answer], ecx
    jmp output
    GO:
    bsr eax, dword[n]
    mov dword[r_prev], eax
    mov cl, 32
    sub cl, al
    shl dword[n], cl
    shr dword[n], cl
    mov dword[m], eax
    add dword[k], 1
    
    Cnk_func:
    mov eax, dword[m]
    cmp eax, dword[k]
    jne coo
    mov eax, 1
    jmp exit_for
    coo:
    cmp eax, dword[k]
    jl end
    cmp dword[k], 0
    jne conte
    mov eax, 1
    jmp exit_for
    conte:
    cmp dword[k], 0
    jl end
    mov ecx, 1
    CNK_for:
    cmp ecx, dword[k]
    jg exit_for
    mov ebx, dword[m]
    sub ebx, dword[k]
    add ebx, ecx
    mov eax, dword[Cnk]
    mul ebx
    xor edx, edx
    div ecx
    mov dword[Cnk], eax 
    inc ecx
    jmp CNK_for
    exit_for:
    
    add dword[answer], eax
    dec dword[k]
    for:
    cmp dword[n], 0
    je end
    bsr eax, dword[n]
    mov edx, dword[r_prev]
    mov dword[r_prev], eax
    mov cl, 32
    sub cl, al
    shl dword[n], cl
    shr dword[n], cl
    sub edx, eax
    sub dword[m], edx
    sub edx, 1
    sub dword[k], edx
    add dword[r_sum], edx
   
   
 
    Cnk_func2:
    sub dword[k], 1
    mov eax, dword[m]
    cmp eax, dword[k]
    jne cooo
    mov eax, 1
    jmp exit_for2
    cooo:
    cmp eax, dword[k]
    jl end
    cmp dword[k], 0
    jne contee
    mov eax, 1
    jmp exit_for2
    contee:
    cmp dword[k], 0
    jl end
    mov dword[Cnk], 1
    mov ecx, 1
    CNK_for2:
    cmp ecx, dword[k]
    jg exit_for2
    mov ebx, dword[m]
    sub ebx, dword[k]
    add ebx, ecx
    mov eax, dword[Cnk]
    mul ebx
    xor edx, edx
    div ecx
    mov dword[Cnk], eax 
    inc ecx
    jmp CNK_for2
    exit_for2:
    add dword[answer], eax
    inc dword[k]
    jmp for
    exit_forr2:
    add dword[answer], eax
    jmp for
    end:
    
    mov eax, dword[r_prev]
    add dword[r_sum], eax
    mov eax, dword[r_sum]
    cmp eax, dword[k_copy]
    jne output
    add dword[answer], 1
    output:
    mov eax, dword[answer]
    call io_print_udec
    xor eax, eax
    ret