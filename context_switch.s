.global activate
.global getmsr
.global setmsr
.global test
test:
    svc 1
    bx lr

activate:
    mov r0, #0x10
    msr SPSR, r0
    mov ip, sp
    msr CPSR_c, #0xdf
    mov sp, ip
    msr CPSR_c, #0xd3
    ldr lr, =usermain
    movs pc, lr

getmsr:
    mov r12, sp
    push {r11, r12, lr, pc}
    sub r11, r12, #4
    mrs r3, SPSR
    mov r0, r3
    ldmfd sp, {r11,sp,pc}


setmsr:
    mov r12, sp
    push {r11, r12, lr, pc}
    sub r11, r12, #4
    sub sp, sp, #8
    msr SPSR, r0
    sub sp, r11, #0xC
    ldmfd sp, {r11,sp,pc}