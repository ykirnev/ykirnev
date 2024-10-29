extern io_get_udec, io_print_udec, io_print_char
section .data
a11 dd 0
a12 dd 0
a21 dd 0
a22 dd 0
b1 dd 0
b2 dd 0
x dd 0
y dd 0
section .text
global main
main:
  mov ebp, esp
  call io_get_udec
  mov dword[a11], eax
  call io_get_udec
  mov dword[a12], eax
  call io_get_udec
  mov dword[a21], eax
  call io_get_udec
  mov dword[a22], eax
  call io_get_udec
  mov dword[b1], eax
  call io_get_udec
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
  mov ecx, dword[a21]
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
  mov ecx, dword[a21]
  not ecx
  and eax, ecx
  and eax, dword[a22]
  and eax, dword[b1]
  or dword[x], eax




  mov eax, dword[a11]
  not eax
  and eax, dword[a12]
  and eax, dword[b1]
  or dword[y], eax

  mov eax, dword[a21]
  not eax
  and eax, dword[a22]
  and eax, dword[b2]
  or dword[y], eax

  mov eax, dword[a12]
  not eax
  mov ecx, dword[b1]
  not ecx
  and eax, ecx
  and eax, dword[a21]
  and eax, dword[a22]
  and eax, dword[b2]
  or dword[y], eax

  mov eax, dword[a11]
  mov ecx, dword[a12]
  not ecx
  and eax, ecx
  mov ecx, dword[b2]
  not ecx
  and eax, ecx
  and eax, dword[a21]
  and eax, dword[a22]
  and eax, dword[b1]
  or dword[y], eax

  mov eax, dword[a11]
  and eax, dword[a12]
  mov ecx, dword[b1]
  not ecx
  and eax, ecx
  mov ecx, dword[a22]
  not ecx
  and eax, ecx
  and eax, dword[a21]
  and eax, dword[b2]
  or dword[y], eax

  mov eax, dword[a11]
  and eax, dword[a12]
  mov ecx, dword[b2]
  not ecx
  and eax, ecx
  mov ecx, dword[a22]
  not ecx
  and eax, ecx
  and eax, dword[b1]
  or dword[y], eax

  mov eax, dword[a11]
  and eax, dword[a12]
  and eax, dword[b1]
  and eax, dword[a21]
  and eax, dword[a22]
  and eax, dword[b2]
  or dword[y], eax

  mov eax, dword[x]
  call io_print_udec
  mov eax, ' '
  call io_print_char
  mov eax, dword[y]
  call io_print_udec

  xor eax, eax
  ret