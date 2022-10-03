#include "nanoshell/shell.h"
#include "multiboot2.h"
#include "IO/printk.h"
#include "utils.h"
#include "mem/physical.h"

void lsmmap(__unused char *arg)
{
	uint64_t length = 0, avail_length = 0;
	int col_width = 10;

	printk("%*s | %*s | %*s |\n",
		col_width, "Address",
		col_width, "Length",
		col_width, "Type");

	for (multiboot_uint32_t i = 0; i < mapping.nb; i++)
	{
		multiboot_memory_map_t *entry = mapping.mmap->entries + i;

		printk("%-*gx | %-*gu | %-*t |\n",
			col_width, entry->addr,
			col_width, entry->len,
			col_width, entry->type);

		length += entry->len;
		if (entry->type == MULTIBOOT_MEMORY_AVAILABLE)
			avail_length += entry->len;
	}
	uint64_t mib_tot = length / 1024 / 1024;
	uint64_t mib_avail = avail_length / 1024 / 1024;
	printk("Total length: %guMB, available length: %guMB\n", mib_tot, mib_avail);
}
