#include "fat16.h"
#include "ata.h"
#include "vga_video.h"
#include "string.h"

static fat16_bpb_t bpb;
static uint32_t fat_start_lba;
static uint32_t root_dir_start_lba;
static uint32_t data_start_lba;

static uint8_t disk_read_sector(uint32_t lba, uint8_t* buffer) {
    return ata_read_sector(lba, buffer);
}

void fat16_init() {
    uint8_t sector[512];

    if(!disk_read_sector(0, sector)) {
        vga_print("FAT16: Falha ao ler boot sector\n");
        return;
    }

    memcpy(&bpb, sector, sizeof(fat16_bpb_t));

    fat_start_lba = bpb.reserved_sectors;
    root_dir_start_lba = fat_start_lba + (bpb.fat_count * bpb.sectors_per_fat);
    uint32_t root_dir_sectors = ((bpb.root_dir_entries * 32) + (bpb.bytes_per_sector - 1)) / bpb.bytes_per_sector;
    data_start_lba = root_dir_start_lba + root_dir_sectors;

    vga_print("FAT16: Sistema inicializado\n");
}

static void fat16_print_filename(fat16_dir_entry_t* entry) {
    char name[13];
    int i, j = 0;

    for(i = 0; i < 8; i++) {
        if(entry->name[i] == ' ') break;
        name[j++] = entry->name[i];
    }

    if(entry->name[8]!= ' ') {
        name[j++] = '.';
        for(i = 8; i < 11; i++) {
            if(entry->name[i] == ' ') break;
            name[j++] = entry->name[i];
        }
    }
    name[j] = 0;
    vga_print(name);
}

int fat16_list_root() {
    uint8_t sector[512];
    uint32_t entries_per_sector = bpb.bytes_per_sector / sizeof(fat16_dir_entry_t);

    for(uint32_t i = 0; i < bpb.root_dir_entries; i += entries_per_sector) {
        uint32_t sector_lba = root_dir_start_lba + (i / entries_per_sector);
        if(!disk_read_sector(sector_lba, sector)) return 0;

        fat16_dir_entry_t* entries = (fat16_dir_entry_t*)sector;
        for(uint32_t j = 0; j < entries_per_sector; j++) {
            if(entries[j].name[0] == 0x00) return 1;
            if(entries[j].name[0] == 0xE5) continue;
            if(entries[j].attr & FAT16_ATTR_VOLUME_ID) continue;

            fat16_print_filename(&entries[j]);
            if(entries[j].attr & FAT16_ATTR_DIRECTORY) {
                vga_print(" <DIR>\n");
            } else {
                vga_print("\n");
            }
        }
    }
    return 1;
}

int fat16_read_file(const char* filename, uint8_t* buffer, uint32_t buf_size) {
    (void)filename;
    (void)buffer;
    (void)buf_size;
    vga_print("FAT16: Leitura nao implementada\n");
    return 0;
}
