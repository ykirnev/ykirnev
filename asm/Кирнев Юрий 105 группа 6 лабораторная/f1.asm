global f1; e^x + 2
global f1pr; e^x

section .rodata
    double_two dq 2.0

section .text

f1: ;e^x + 2
    push ebp ;пролог
    mov ebp, esp
    
    and esp, 0xfffffff0 ;выравнивание стека
    sub esp, 16

    finit
    fldl2e  
    fld qword[ebp + 8]
    fmulp                        ;2^ (log2(e)*x)
    fld1
    fld st1
    fprem
    f2xm1
    faddp st1, st0
    fscale
    fstp st1
    fld1
    faddp
    fld1
    faddp
    mov esp, ebp
    pop ebp
    ret

f1pr: ;e^x
    push ebp ;пролог
    mov ebp, esp
    
    and esp, 0xfffffff0 ;выравнивание стека
    sub esp, 16

    finit
    fldl2e  
    fld qword[ebp + 8]
    fmulp                        ;2^ (log2(e)*x)
    fld1
    fld st1
    fprem
    f2xm1
    faddp st1, st0
    fscale
    fstp st1
    
    mov esp, ebp
    pop ebp
    ret