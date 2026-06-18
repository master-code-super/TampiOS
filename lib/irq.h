#ifndef IRQ_H
#define IRQ_H
#include "registers.h"  // <- USA O COMUM

void irq_install_handler(int irq, void (*handler)(void));
void irq_remap(void);
void irq_handler(registers_t regs);

#endif
