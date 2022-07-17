#include "nanoshell/shell.h"
#include "multiboot.h"
#include "IO/printk.h"
#include "utils.h"

extern multiboot_info_t *_mbd;

void lsmmap(__unused char *arg)
{
	multiboot_info_t *mbd = _mbd;

	uint32_t mb = 1024 * 1024;
	if (mbd->flags & MULTIBOOT_INFO_MEMORY)
		printk("Memory lower: %u, Memory upper starts at: %x\n",
			mbd->mem_lower,
			mbd->mem_upper + mb);

	size_t inc = sizeof(multiboot_memory_map_t);
	uint64_t length = 0, avail_length = 0;
	int col_width = 10;

	printk("%*s | %*s | %*s | %*s |\n",
		col_width, "Size",
		col_width, "Address",
		col_width, "Length",
		col_width, "Type");
	for (size_t i = 0; i < mbd->mmap_length; i += inc)
	{
		multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)(mbd->mmap_addr + i);

		printk("%-*u | %-*gx | %-*gu | %-*t |\n",
			col_width, mmap->size,
			col_width, mmap->addr,
			col_width, mmap->len,
			col_width, mmap->type);

		length += mmap->len;
		if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
			avail_length += mmap->len;
	}
	uint64_t mib_tot = length / 1024 / 1024;
	uint64_t mib_avail = avail_length / 1024 / 1024;
	printk("Total length: %guMB, available length: %guMB\n", mib_tot, mib_avail);
}
