#include "vga_video.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint8_t current_color = 0x07; // Cinza claro no preto
uint16_t cursor_pos = 0;
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

void vga_set_color(uint8_t fg, uint8_t bg) {
    current_color = (bg << 4) | (fg & 0x0F);
}

void vga_clear() {
    for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = (current_color << 8) | ' ';
    }
    cursor_pos = 0;
}

void vga_init() {
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga_clear();
}

void vga_putchar(char c) {
    if(c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    } else if(c == '\r') {
        cursor_pos -= (cursor_pos % VGA_WIDTH);
    } else if(c == '\t') {
        vga_putchar(' ');
        vga_putchar(' ');
        vga_putchar(' ');
        vga_putchar(' ');
    } else {
        vga_buffer[cursor_pos] = (current_color << 8) | c;
        cursor_pos++;
    }

    // Scroll automático
    if(cursor_pos >= VGA_WIDTH * VGA_HEIGHT) {
        for(int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
            vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
        }
        for(int i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++) {
            vga_buffer[i] = (current_color << 8) | ' ';
        }
        cursor_pos = VGA_WIDTH * (VGA_HEIGHT - 1);
    }
}

void vga_print(const char* str) {
    while(*str) {
        vga_putchar(*str++);
    }
}
