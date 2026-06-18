#include "ata.h"
#include "io.h"
#include "vga_video.h"

void ata_init() {
    outb(ATA_PRIMARY_CTRL, 0x04);
    outb(ATA_PRIMARY_CTRL, 0x00);
    vga_print("ATA: Controlador inicializado\n");
}

static void ata_wait_bsy() {
    while(inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & 0x80);
}

static void ata_wait_drq() {
    while(!(inb(ATA_PRIMARY_IO + ATA_REG_STATUS) & 0x08));
}

uint8_t ata_read_sector(uint32_t lba, uint8_t* buffer) {
    ata_wait_bsy();

    outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_PRIMARY_IO + ATA_REG_SECCOUNT0, 1);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA0, (uint8_t)lba);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA1, (uint8_t)(lba >> 8));
    outb(ATA_PRIMARY_IO + ATA_REG_LBA2, (uint8_t)(lba >> 16));
    outb(ATA_PRIMARY_IO + ATA_REG_COMMAND, ATA_CMD_READ_PIO);

    ata_wait_bsy();
    ata_wait_drq();

    for(int i = 0; i < 256; i++) {
        uint16_t data = inw(ATA_PRIMARY_IO + ATA_REG_DATA);
        buffer[i*2] = data & 0xFF;
        buffer[i*2 + 1] = (data >> 8) & 0xFF;
    }

    return 1;
}
