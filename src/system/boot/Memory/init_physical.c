#include "mem/physical.h"
#include "mem/allocator.h"
#include "panic.h"

physical_memory_t phys_alloc;

__unused void init_physical(void) {
	uintptr_t min = KERNEL_START;
	ptrdiff_t kern_size = (KERNEL_END - KERNEL_START);

	for (multiboot_uint32_t i = 0; i < mapping.nb; i++) {
		multiboot_memory_map_t *entry = mapping.mmap->entries + i;

		if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
			uintptr_t addr = entry->addr;
			if (addr < min)
				continue;
			if (kern_size > (long) entry->len)
				continue;

			phys_alloc.entry = entry;
			init_bitmap(kern_size);
			break;
		}
	}

	if (phys_alloc.data == NULL)
		kpanic("Error: %s:%d: No available memory found", __FILE__, __LINE__);
}
