#ifndef MEMORY_PAGING_H
#define MEMORY_PAGING_H

#include <stdint.h>
#include <stddef.h>
#include "utils.h"

#define KERNEL_VIRT_BASE 0xC0000000

// Page directory entry for now it is 4KB aligned (should be adapted to allow for different page sizes)
typedef struct
{
	uint32_t present : 1;
	uint32_t rw : 1;
	uint32_t us : 1;
	uint32_t write_through : 1;
	uint32_t cache_disabled : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t page_size : 1;
	uint32_t global : 1;
	uint32_t available : 3;
	uint32_t page_address : 20;
} __packed page_directory_t;



#endif
