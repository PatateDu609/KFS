#ifndef KFS_VIRTUAL_H
#define KFS_VIRTUAL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

// Masking offset bits (last 12 bits, or last 3 bytes)
#define GET_VIRTUAL_ADDRESS(addr) (((uint32_t)addr) & 0xFFFFF000)
#define PAGE_TABLE_PRESENT 1
#define PAGE_TABLE_READ_WRITE 1 << 1

#define PAGE_FRAME_PRESENT 1
#define PAGE_FRAME_READ_WRITE 1 << 1


typedef uint32_t page_directory_entry_conv_t;

typedef uint32_t page_table_entry_conv_t;

extern page_directory_entry_conv_t boot_page_directory[1024];

void init_paging();

// Defined in assembly src/system/boot/Memory/load.s
void enable_paging(void);
void flush_cr3(uint32_t addr);

#endif //KFS_VIRTUAL_H
