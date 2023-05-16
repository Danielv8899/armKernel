.global _start
_start:
    mov r0, #0x08
    ldr r1, =interrupt_table
    ldr r3, =interrupt_table_end
load:
    ldr r2, [r1, #0x0]
    str r2, [r0, #0x0]
    add r0, r0, #0x4
    add r1, r1, #0x4
    cmp r1, r3
    bne load
    ldr sp, =0x07FFFFF0
    bl main

interrupt_table:
    ldr pc, svc_entry_addr
    svc_entry_addr: .word svc_entry
interrupt_table_end: