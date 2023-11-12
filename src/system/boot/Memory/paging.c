#include "mem/virtual.h"
#include "CPU/GDT.h"
#include "mem/physical.h"
#include "IO/terminal.h"


// terminal mapping: 0000000000 1011100000 0000000000
// Identity Maps terminal, and GDT locations
__aligned(FRAME_SIZE)
page_table_entry_conv_t first_table[1024];

// Map for the higher half kernel
__aligned(FRAME_SIZE)
page_table_entry_conv_t kernel_table[1024];

__unused void init_paging() {
	for (size_t i = 0; i < 1024; i++) {
		boot_page_directory[i] = PAGE_TABLE_READ_WRITE;
		first_table[i] =  PAGE_FRAME_READ_WRITE;
	}

	boot_page_directory[0] = GET_VIRTUAL_ADDRESS(first_table) | PAGE_TABLE_READ_WRITE | PAGE_TABLE_PRESENT;
	boot_page_directory[768] = GET_VIRTUAL_ADDRESS(kernel_table) | PAGE_TABLE_READ_WRITE | PAGE_TABLE_PRESENT;

//	first_table[2] = GET_VIRTUAL_ADDRESS(GDT_ADDR) | PAGE_FRAME_READ_WRITE | PAGE_FRAME_PRESENT;
//	first_table[736] = GET_VIRTUAL_ADDRESS(TERMINAL_VM86_ADDR) | PAGE_FRAME_READ_WRITE | PAGE_FRAME_PRESENT;

	for (size_t i = 0; i < 1024; i++) {
		first_table[i] = GET_VIRTUAL_ADDRESS(i * FRAME_SIZE) | PAGE_FRAME_READ_WRITE | PAGE_FRAME_PRESENT;
		kernel_table[i] = GET_VIRTUAL_ADDRESS(KERNEL_START + i * FRAME_SIZE) | PAGE_FRAME_READ_WRITE | PAGE_FRAME_PRESENT;
	}
}
