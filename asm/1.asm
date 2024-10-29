extern io_get_dec, io_print_dec
section .data
a11 dd 0
a12 dd 0
a22 dd 0
b1 dd 0
b2 dd 0

x dd 0
y dd 0
section .text
global main
main:
  mov ebp, esp
  call io_get_dec
  mov dword[a11], eax
  call io_get_dec
  mov dword[a12], eax
  call io_get_dec
  mov dword[a21], eax
  call io_get_dec
  mov dword[a22], eax
  call io_get_dec
  mov dword[b1], eax
  call io_get_dec
  mov dword[b2], eax
  
  mov eax, dword[a11]
  mov ecx, dword[a12]
  not ecx
  and eax, ecx
  and eax, dword[b1]
  or dword[x], eax

  mov eax, dword[a21]
  mov ecx, dword[a22]
  not ecx
  and eax, ecx
  and eax, dword[b2]
  or dword[x], eax

  mov eax, dword[a11]
  not eax
  and eax, dword[a12]
  mov ecx, dword[b1]
  not ecx
  and eax, ecx
  and eax, dword[a21]
  and eax, dword[a22]
  and eax, dword[b2]
  or dword[x], eax

  mov eax, dword[a11]
  not eax
  and eax, dword[a12]
  mov ecx, dword[b2]
  not ecx
  and eax, ecx
  and eax, dword[a21]
  and eax, dword[a22]
  and eax, dword[b1]
  or dword[x], eax

  mov eax, dword[a11]
  and eax, dword[a12]
  mov ecx, dword[b1]
  not ecx
  and eax, ecx
  and ecx, dword[a21]
  not ecx
  and eax, ecx
  and eax, dword[a22]
  and eax, dword[b2]
  or dword[x], eax

  mov eax, dword[a11]
  and eax, dword[a12]
  mov ecx, dword[b2]
  not ecx
  and eax, ecx
  and ecx, dword[a21]
  not ecx
  and eax, ecx
  and eax, dword[a22]
  and eax, dword[b1]
  or dword[x], eax






  
  



  xor eax, eax
  ret
