#ifndef VGA_VIDEO_H
#define VGA_VIDEO_H

// Cores padrão do modo VGA
typedef enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
} vga_color_t;

// Inicializa a tela (limpa o lixo do Grub/Bios)
void vga_init(vga_color_t fg, vga_color_t bg);

// A função mágica que você queria
void vga_print(const char* str);

#endif