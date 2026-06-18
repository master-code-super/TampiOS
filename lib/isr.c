#include "isr.h"
#include "vga_video.h"

void isr_handler(registers_t regs) {
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_RED);
    vga_print("EXCEPTION: HALTED\n");
    for(;;);
}

void isr_install() {}
