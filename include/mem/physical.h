#ifndef MEM_PHYSICAL_H
#define MEM_PHYSICAL_H

#include <stddef.h>
#include "../libc/stdint.h"
#include "../multiboot2.h"

#define FRAME_SIZE 0x1000 // 4KB
#define ALIGN(ptr, alignment) (((ptr) + (alignment) - 1) & ~((alignment) - 1))

typedef struct {
	uint8_t *data;
	size_t size;
} physical_memory_t;

typedef struct
{
	struct multiboot_tag_mmap *mmap;
	multiboot_uint32_t nb;
} mem_mapping_t;

extern physical_memory_t pmem;
extern mem_mapping_t mapping;

#endif
