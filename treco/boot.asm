; Assinatura Multiboot padrão para o QEMU reconhecer o Kernel
MODULEALIGN equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MODULEALIGN | MEMINFO
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global _start
extern kernel_main

_start:
    cli             ; Desliga interrupções do processador por segurança
    call kernel_main ; Pula direto para a função kernel_main do seu kernel.c
    hlt             ; Se o kernel retornar, trava o computador