#include "vga_video.h"

// Ponteiro para a memória de vídeo VGA (modo texto)
static volatile unsigned short* const VGA_BUFFER = (unsigned short*) 0xB8000;
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

static int vga_column = 0;
static int vga_row = 0;
static unsigned char vga_color_attribute = 0;

// Função interna para gerar o byte de cor (Texto/Fundo)
static inline unsigned char vga_entry_color(vga_color_t fg, vga_color_t bg) {
    return fg | bg << 4;
}

// Inicializa e limpa a tela
void vga_init(vga_color_t fg, vga_color_t bg) {
    vga_color_attribute = vga_entry_color(fg, bg);
    vga_column = 0;
    vga_row = 0;

    // Preenche a tela com espaços em branco
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            VGA_BUFFER[index] = ' ' | (vga_color_attribute << 8);
        }
    }
}

// Coloca um caractere na tela e trata quebras de linha (\n)
static void vga_putchar(char c) {
    if (c == '\n') {
        vga_column = 0;
        vga_row++;
    } else {
        const int index = vga_row * VGA_WIDTH + vga_column;
        VGA_BUFFER[index] = c | (vga_color_attribute << 8);
        
        vga_column++;
        if (vga_column >= VGA_WIDTH) {
            vga_column = 0;
            vga_row++;
        }
    }

    // Scroll simples: se passar da última linha, reseta pro topo 
    // (o ideal seria arrastar a memória para cima, mas para começar isso basta)
    if (vga_row >= VGA_HEIGHT) {
        vga_row = 0; 
    }
}

// A sua função simplificada
void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}