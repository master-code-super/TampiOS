#include "irq.h"
#include "io.h"

void irq_install() {
    // Remapeia a PIC: IRQ 0-15 pra int 32-47
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void irq_handler(registers_t regs) {
    // Manda EOI pro PIC
    if(regs.int_no >= 40) {
        outb(0xA0, 0x20); // Slave
    }
    outb(0x20, 0x20); // Master
}
