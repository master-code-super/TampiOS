#ifndef DISK.H
#define DISK.H
#include <stdint.h>
#include <stddef.h>
#define ATA_PRIMARY_IO 0x1F0
#define ATA_PRIMARY_CTRL 0x3F6
#define ATA_ERROR 0x01
#define ATA_SECTOR_COUNT 0x02
#define ATA_LBA_LOW 0x03
#define ATA_LBA_MID 0x04
#define ATA_LBA_HIGH 0x05
#define ATA_DRIVE_HEAD 0x06
#define ATA_COMMAND 0x07
#define ATA_STATUS 0x07
#define ATA_CMD_READ_PIO 0x20
#define ATA_STATUS_ERR 0x01 
#define ATA_STATUS_DRQ 0x08 
#define ATA_STATUS_BSY 0x80
typedef struct {
uint8_t status;
