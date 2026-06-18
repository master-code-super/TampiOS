#include "power.h"
#include "io.h"

void power_reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE); // Reset via teclado 8042

    // Se falhar, tenta triple fault
    asm volatile("cli");
    asm volatile("int $0x00");
}

void power_shutdown() {
    // QEMU/Bochs shutdown via ACPI
    outw(0x604, 0x2000);
    
    // VirtualBox shutdown via ACPI  
    outw(0x4004, 0x3400);
    
    // Se nada funcionar, halt
    asm volatile("cli");
    asm volatile("hlt");
}
