#include "timer.h"
#include "io.h"
#include "irq.h"      // <- FALTAVA ESSE AQUI
#include "task.h"

void timer_handler() {
    task_switch();
}

void timer_init(unsigned int freq) {
    irq_install_handler(0, timer_handler); // agora ele conhece

    unsigned int divisor = 1193180 / freq;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}
