#ifndef MEM_PHYSICAL_H
#define MEM_PHYSICAL_H

#include <stddef.h>
#include "../libc/stdint.h"
#include "../multiboot2.h"

#define FRAME_SIZE (0x1000) // 4KB
#define ALIGN(val, alignment) (((val) + (alignment) - 1) & ~((alignment) - 1))

typedef struct {
	struct multiboot_mmap_entry *entry;

	// bitmap pointer (should be right after the kernel's end)
	uint32_t *bitmap;
	uint32_t bitmap_size;

	// Stores the index of the last allocated bit.
	uint32_t last_alloc_bit;

	// pointer to the start of the actual data section.
	uint32_t *data;
	uint32_t nb_pages;
} physical_memory_t;

typedef struct
{
	struct multiboot_tag_mmap *mmap;
	multiboot_uint32_t nb;
} mem_mapping_t;

// A bitmap Physical Allocator.
extern physical_memory_t phys_alloc;
extern mem_mapping_t mapping;

// Provided by the linker itself, its address represents the start of the kernel.
extern uint32_t ld_start;
// Provided by the linker itself, its address represents the end of the kernel.
extern uint32_t ld_end;

#define KERNEL_START ((uint32_t)&ld_start)
#define KERNEL_END ((uint32_t)&ld_end)

#endif
