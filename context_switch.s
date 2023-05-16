.global activate
.global getmsr
.global setmsr
.global test
.global svc_entry

test:
    svc 1
    bx lr

activate:
    mov ip, sp
    push {r4,r5,r6,r7,r8,r9,r10,fp,ip,lr}
    ldmfd r0!, {ip,lr}
    msr SPSR, ip
    msr CPSR_c, #0xdf
    mov sp, r0
    pop {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,fp,ip,lr}
    msr CPSR_c, #0xd3
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

svc_entry:

    msr CPSR_c, #0xDF
	push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,fp,ip,lr}
	mov r0, sp
	msr CPSR_c, #0xD3 
    mrs ip, SPSR
    stmfd r0!, {ip,lr}
    pop {r4,r5,r6,r7,r8,r9,r10,fp,ip,lr}
    mov sp, ip
    bx lr