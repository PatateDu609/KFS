#include "mem/virtual.h"
#include "CPU/GDT.h"
#include "mem/physical.h"
#include "IO/terminal.h"


// terminal mapping: 0000000000 1011100000 0000000000
// 0x800
// Identity Maps terminal, and GDT locations
__aligned(FRAME_SIZE)
page_table_entry_conv_t first_table[1024];

__unused void finalize_paging_setup() {
	first_table[2] = GET_VIRTUAL_ADDRESS(GDT_ADDR) | PAGE_FRAME_READ_WRITE | PAGE_FRAME_PRESENT;
	first_table[736] = GET_VIRTUAL_ADDRESS(TERMINAL_VM86_ADDR) | PAGE_FRAME_READ_WRITE | PAGE_FRAME_PRESENT;

	boot_page_directory[0] = GET_VIRTUAL_ADDRESS(first_table - 0xC0000000) | PAGE_TABLE_READ_WRITE | PAGE_TABLE_PRESENT;
	reset_cr3();
}
