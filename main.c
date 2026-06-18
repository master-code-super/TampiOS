// esse kernel e feito para ser menor do linus torvals mas estou sendo inspirado nele

#include "lib/gdt.h"
#include "lib/idt.h"
#include "lib/irq.h"
#include "lib/timer.h"
#include "lib/task.h"
#include "lib/vga_video.h"

void task2() {
    while(1) {
        vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
        vga_print("Task 2\n");
        for(volatile int i = 0; i < 10000000; i++);
    }
}

void main() {
    gdt_init();
    idt_init();
    irq_install();
    vga_init();

    vga_set_color(VGA_COLOR_YELLOW, VGA_COLOR_BLUE);
    vga_print("TempiOS Multitask 32-bits 🏴‍☠️💙\n");

    task_init();
    task_create(task2);
    timer_init(100);

    asm volatile("sti");

    while(1) {
        vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        vga_print("Task 1\n");
        for(volatile int i = 0; i < 10000000; i++);
    }
}
