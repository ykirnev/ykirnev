extern io_get_dec, io_print_dec, io_print_char
section .data
max1 dd 0
max2 dd 0
max3 dd 0
n dd 0
section .text
global main
main:
    mov ebp, esp
    call io_get_dec
    sub eax, 2
    mov dword[n], eax
    call io_get_dec
    mov dword[max1], eax
    call io_get_dec
    cmp eax, dword[max1]
    ja change1
    mov dword[max2], eax
    jmp afterchange1
    
    change1:
    mov ebx, dword[max1]
    mov dword[max2], ebx
    mov dword[max1], eax
    afterchange1:
  
    for:
    mov ecx, dword[n]
    jecxz exit
    dec ecx
    mov dword[n], ecx
    call io_get_dec
    cmp eax, dword[max1]
    ja changemax1
    cmp eax, dword[max2]
    ja changemax2
    cmp eax, dword[max3]
    ja changemax3
    jmp for
    
    
   changemax1:
   mov ebx, dword[max2]
   mov dword[max3], ebx
   mov ebx, dword[max1]
   mov dword[max2], ebx
   mov dword[max1], eax
   jmp for
   
   changemax2:
   mov ebx, dword[max2]
   mov dword[max3], ebx
   mov dword[max2], eax
   jmp for
   
   changemax3:
   mov dword[max3], eax
   jmp for
   
   exit:
   mov eax, dword[max1]
   call io_print_dec
   mov eax, ' '
   call io_print_char
   mov eax, dword[max2]
   call io_print_dec
   mov eax, ' '
   call io_print_char
   mov eax, dword[max3]
   call io_print_dec
    
 
   xor eax, eax
   ret