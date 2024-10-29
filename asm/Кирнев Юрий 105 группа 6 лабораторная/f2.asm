global f2 ; -2x + 8
global f2pr ; -2
section .rodata
    double_min_two dq -2.0
    double_eight dq 8.0

section .text
f2: ;-2x + 8
    push ebp ;пролог
    mov ebp, esp

    and esp, 0xfffffff0 ;выравнивание стека
    sub esp, 16

    finit
    fld qword[ebp + 8]
    fld qword[double_min_two]
    fmulp
    fld qword[double_eight]
    faddp
    mov esp, ebp
    pop ebp
    ret

f2pr: ;-2
    push ebp ;пролог
    mov ebp, esp

    and esp, 0xfffffff0 ;выравнивание стека
    sub esp, 16

    finit
    fld qword[double_min_two]
    
    mov esp, ebp
    pop ebp
    ret
    






