#ifndef FAT16_H
#define FAT16_H

#include "types.h"

typedef struct {
    uint8_t jmp[3];
    uint8_t oem[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t fat_count;
    uint16_t root_dir_entries;
    uint16_t total_sectors_16;
    uint8_t media_descriptor;
    uint16_t sectors_per_fat;
    uint16_t sectors_per_track;
    uint16_t head_count;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;
    uint8_t drive_number;
    uint8_t reserved;
    uint8_t boot_signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t fs_type[8];
} __attribute__((packed)) fat16_bpb_t;

typedef struct {
    uint8_t name[11];
    uint8_t attr;
    uint8_t nt_reserved;
    uint8_t created_time_tenth;
    uint16_t created_time;
    uint16_t created_date;
    uint16_t last_access_date;
    uint16_t first_cluster_high;
    uint16_t modified_time;
    uint16_t modified_date;
    uint16_t first_cluster_low;
    uint32_t file_size;
} __attribute__((packed)) fat16_dir_entry_t;

#define FAT16_ATTR_READ_ONLY 0x01
#define FAT16_ATTR_HIDDEN 0x02
#define FAT16_ATTR_SYSTEM 0x04
#define FAT16_ATTR_VOLUME_ID 0x08
#define FAT16_ATTR_DIRECTORY 0x10
#define FAT16_ATTR_ARCHIVE 0x20

void fat16_init();
int fat16_list_root();
int fat16_read_file(const char* filename, uint8_t* buffer, uint32_t buf_size);

#endif
