bits 32

global irq0
global irq1
global idt_load
extern irq_handler



irq_common:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push eax
    call irq_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret

irq0:
    push byte 0
    jmp irq_common

irq1:
    push byte 1
    jmp irq_common
