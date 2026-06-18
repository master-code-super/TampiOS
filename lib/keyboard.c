#include "keyboard.h"
#include "vga_video.h"

// Tipos pro kernel sem stdlib 👑
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#define KB_DATA_PORT   0x60
#define KB_STATUS_PORT 0x64

// inb inline pq não temos header compartilhado
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Scancode US básico pra teste
static char scancode_to_ascii[] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0, '\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '
};

char keyboard_getchar() {
    uint8_t scancode;
    
    // Espera tecla ser pressionada
    do {
        while(!(inb(KB_STATUS_PORT) & 1)); // Espera buffer cheio
        scancode = inb(KB_DATA_PORT);
    } while(scancode & 0x80); // Ignora key release
    
    if(scancode < sizeof(scancode_to_ascii))
        return scancode_to_ascii[scancode];
        
    
    return 0;
}

void keyboard_init() {
}
// keyboard_set_callback(shell_keypress);

