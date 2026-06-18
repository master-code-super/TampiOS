// esse kernel e feito para ser menor do linus torvals mas estou sendo espirado nele

#include "lib/vga_video.h" // Importando o mesmo cabeçalho .c
#include "lib/string.h"
#include "lib/keyboard.h"


void kernel_main() {
	kb_init();
    vga_init(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    //  vga_print rodando puro!
    vga_print("=============\n");
    vga_print("TAMPI LINUX\n");
    vga_print("=============\n");
	
	// strcpy(nome, "alguma coisa");
	
	
	while(1);
}
