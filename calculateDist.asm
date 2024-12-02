section .text
bits 64
default rel
global calculateDist

calculateDist:
    ;write your code here
    push rsi
    push rbp
    mov rbp, rsp
    add rbp, 16
    
    ;n@rcx, x1@rdx, x2@r8, y1@r9,  y2,z at stack
    mov r10, rdx
    mov r11, r8
    mov r12, r9
    mov r13, [rbp+40]
    mov r14, [rbp+48]
    
L1:
    movsd xmm0, qword[r11]
    subsd xmm0, qword[r10]
    
    mulsd xmm0, xmm0
    
    movsd xmm1, qword[r13]
    subsd xmm1, qword[r12]
    
    mulsd xmm1, xmm1
    
    addsd xmm0, xmm1
    
    sqrtsd xmm0, xmm0
    
    movsd qword[r14], xmm0
    
    add r10, 8
    add r11, 8
    add r12, 8
    add r13, 8
    add r14, 8
    
    LOOP L1
    pop rbp
    pop rsi
    ret