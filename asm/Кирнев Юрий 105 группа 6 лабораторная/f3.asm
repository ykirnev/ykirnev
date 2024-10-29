global f3; −5/x
global f3pr; 5/(x^2)

section .rodata
    double_five dq 5.0
    double_min_five dq -5.0

section .text
f3: ;−5/x
     push ebp ;пролог
    mov ebp, esp

    and esp, 0xfffffff0 ;выравнивание стека
    sub esp, 16

    finit
    fld qword[double_min_five]
    fld qword[ebp + 8]
    fdivp

    mov esp, ebp
    pop ebp
    ret

f3pr: ; 5/(x^2)
     push ebp ;пролог
    mov ebp, esp

    and esp, 0xfffffff0 ;выравнивание стека
    sub esp, 16

    finit
    fld qword[double_five]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
