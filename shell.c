#include "lib/vga_video.h"
#include "lib/keyboard.h"
#include "lib/string.h"
#include "lib/types.h"
#include "lib/ata.h"
#include "lib/fat16.h"
#include "lib/power.h"

#define CMD_BUF_SIZE 256
#define PROMPT "> "

static char cmd_buffer[CMD_BUF_SIZE];
static uint32_t cmd_pos = 0;

void shell_init() {
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("TempiOS Shell v0.1\n");
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    ata_init();
    fat16_init();

    vga_print("Digite \"help\" para comandos\n\n");
    vga_print(PROMPT);
}

static void shell_clear_buffer() {
    for(uint32_t i = 0; i < CMD_BUF_SIZE; i++) {
        cmd_buffer[i] = 0;
    }
    cmd_pos = 0;
}

static void shell_process_cmd() {
    vga_print("\n");

    if(strcmp(cmd_buffer, "help") == 0) {
        vga_print("Comandos disponiveis:\n");
        vga_print(" help - Mostra ajuda\n");
        vga_print(" clear - Limpa tela\n");
        vga_print(" about - Sobre o TempiOS\n");
        vga_print(" ls - Lista arquivos\n");
        vga_print(" cat - Le arquivo: cat NOME.TXT\n");
        vga_print(" reboot - Reinicia o sistema\n");
        vga_print(" shutdown - Desliga o sistema\n");
    }
    else if(strcmp(cmd_buffer, "clear") == 0) {
        vga_clear();
    }
    else if(strcmp(cmd_buffer, "about") == 0) {
        vga_print("TempiOS - Kernel bare metal x86\n");
        vga_print("Feito na unha em C + ASM 🏴‍☠️💙\n");
    }
    else if(strcmp(cmd_buffer, "ls") == 0) {
        fat16_list_root();
    }
    else if(strncmp(cmd_buffer, "cat ", 4) == 0) {
        char* filename = cmd_buffer + 4;
        uint8_t buffer[2048];
        memset(buffer, 0, 2048);

        if(fat16_read_file(filename, buffer, 2048)) {
            vga_print((char*)buffer);
            vga_print("\n");
        } else {
            vga_print("Arquivo nao encontrado ou erro na leitura\n");
        }
    }
    else if(strcmp(cmd_buffer, "reboot") == 0) {
        vga_print("Reiniciando...\n");
        power_reboot();
    }
    else if(strcmp(cmd_buffer, "shutdown") == 0) {
        vga_print("Desligando...\n");
        power_shutdown();
    }
    else if(cmd_pos > 0) {
        vga_print("Comando nao encontrado: ");
        vga_print(cmd_buffer);
        vga_print("\n");
    }

    shell_clear_buffer();
    vga_print(PROMPT);
}

void shell_handle_key(char c) {
    if(c == '\n') {
        cmd_buffer[cmd_pos] = 0;
        shell_process_cmd();
    }
    else if(c == '\b') {
        if(cmd_pos > 0) {
            cmd_pos--;
            vga_print("\b \b");
        }
    }
    else if(cmd_pos < CMD_BUF_SIZE - 1) {
        cmd_buffer[cmd_pos++] = c;
        char str[2] = {c, 0};
        vga_print(str);
    }
}

void shell_run() {
    while(1) {
        char c = keyboard_getchar();
        if(c) {
            shell_handle_key(c);
        }
    }
}
