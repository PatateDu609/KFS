#include "mem/allocator.h"
#include "panic.h"

void *kmalloc(size_t size) {
	ASSERT(phys_alloc.bitmap != NULL, "memory not initialized");

	static const size_t bits = sizeof(*phys_alloc.bitmap) * 8;

	size = ALIGN(size, FRAME_SIZE);
	size_t nb_pages = size / FRAME_SIZE;
	size_t start_search = phys_alloc.last_alloc_bit == 0 ? 0 : phys_alloc.last_alloc_bit + 1;

	size_t streak = 0, page = start_search;
	for (size_t i = page / bits; i < phys_alloc.bitmap_size && streak < nb_pages; i++) {
		uint32_t byte = phys_alloc.bitmap[i];

		for (size_t j = 0, mask = 1; j < bits && streak < nb_pages; j++, mask <<= 1) {
			if (byte & mask) {
				streak = 0;
			} else if (!streak) {
				page = i * bits + j;
			}

			streak++;
		}
	}

	if (streak < nb_pages)
		return NULL;

	size_t byte = page / bits;
	size_t offset = page % bits;
	for (size_t remaining = nb_pages; remaining > 0; remaining--) {
		uint32_t mask = 0;

		for (size_t i = offset; remaining > 0 && i < bits; i++, remaining = (remaining <= 1) ? 0 : remaining - 1)
			mask |= 1 << i;

		phys_alloc.bitmap[byte] |= mask;

		if (offset >= bits) {
			byte++;
			offset = 0;
		}

		if (remaining == 0) break;
	}
	phys_alloc.last_alloc_bit = page + nb_pages - 1; // Returns the index of the last allocated bit (starting from 0)
	return phys_alloc.data + (page * FRAME_SIZE);
}

void kfree(void *ptr) {
	ASSERT(phys_alloc.bitmap != NULL, "memory not initialized");

	static const size_t bits = sizeof(*phys_alloc.bitmap) * 8;

	ptrdiff_t diff = (uint32_t)ptr - (uint32_t)phys_alloc.data;

	if (diff % FRAME_SIZE != 0) {
		kpanic("kfree: bad pointer\n");
	}

	size_t page = diff / FRAME_SIZE;
	size_t byte = page / bits;
	size_t offset = page % bits;

	phys_alloc.bitmap[byte] &= ~(1 << offset);
}
