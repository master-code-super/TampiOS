#ifndef ISR_H
#define ISR_H
#include "registers.h"  // <- USA O COMUM

void isr_install(void);
void isr_handler(registers_t regs);

#endif
