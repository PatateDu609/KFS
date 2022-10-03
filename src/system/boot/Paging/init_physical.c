#include "mem/physical.h"
#include "panic.h"

extern void *ld_start;
extern void *ld_end;

uintptr_t start = (uintptr_t)&ld_start;
uintptr_t end = (uintptr_t)&ld_end;

physical_memory_t pmem;

static void init_bitmap(void)
{

}

void init_physical(void)
{
	uintptr_t min = start;
	ptrdiff_t kern_size = end - start;

	for (multiboot_uint32_t i = 0; i < mapping.nb; i++)
	{
		multiboot_memory_map_t *entry = mapping.mmap->entries + i;

		if (entry->type == MULTIBOOT_MEMORY_AVAILABLE)
		{
			uintptr_t addr = entry->addr;
			if (addr < min)
				continue;
			if (kern_size > (long)entry->len)
				continue;
			pmem.data = (uint8_t *)ALIGN(addr + kern_size, FRAME_SIZE);
			pmem.size = (entry->addr + entry->len) - (uintptr_t)pmem.data;
			break;
		}
	}

	if (pmem.data == NULL)
		kpanic("Error: %s:%d: No available memory found", __FILE__, __LINE__);

	init_bitmap();
}
