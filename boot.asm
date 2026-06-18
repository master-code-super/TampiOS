section .multiboot
align 4
    dd 0x1BADB002              ; magic
    dd 0x00                    ; flags
    dd - (0x1BADB002 + 0x00)   ; checksum

section .text
[bits 32]
[global start]
[extern main]
; ... resto do código continua igual

[bits 32]
[global start]
[extern main]

start:
    call main
    jmp $

[GLOBAL gdt_flush]
gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret

[GLOBAL idt_flush]
idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    ret

%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_ERRCODE 8
ISR_ERRCODE 13
ISR_ERRCODE 14

extern isr_handler
isr_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret

global irq0
irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub

extern irq_handler
extern timer_handler
irq_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call irq_handler
    call timer_handler
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    sti
    iret
global irq1
irq1:
    cli
    push byte 1
    push byte 33
    jmp irq_common_stub
