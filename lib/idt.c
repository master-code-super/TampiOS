#include "idt.h"

extern void idt_flush(uint32_t);
extern void isr0();
extern void isr8();
extern void isr13();
extern void isr14();
extern void irq0();
extern void irq1();

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].zero = 0;
    idt_entries[num].flags = flags;
}

void idt_init() {
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    for(int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);

    idt_flush((uint32_t)&idt_ptr);
}
