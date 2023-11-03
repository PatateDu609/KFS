#include "mem/allocator.h"
#include "mem/physical.h"
#include <string.h>

void init_bitmap(ptrdiff_t kern_size) {
	uint32_t nb_pages = phys_alloc.entry->len / FRAME_SIZE;
	uint32_t bitmap_size = ALIGN(nb_pages / 8 + nb_pages % 8, FRAME_SIZE);

	phys_alloc.data = (uint32_t *) ALIGN((ptrdiff_t)phys_alloc.entry->addr, FRAME_SIZE);
	phys_alloc.nb_pages = nb_pages;
	phys_alloc.bitmap = (uint32_t *) ALIGN((uint32_t) phys_alloc.entry->addr + kern_size, FRAME_SIZE);
	phys_alloc.bitmap_size = bitmap_size;
	memset(phys_alloc.bitmap, 0, phys_alloc.bitmap_size);

	phys_alloc.last_alloc_bit = 0;

	// Marking as reserved the locations of the kernel and the bitmap itself
	kmalloc(kern_size + phys_alloc.bitmap_size);
}
