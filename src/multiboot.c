#include "multiboot2.h"
#include <stdint.h>
#include "IO/terminal.h"
#include "panic.h"
#include "mem/physical.h"

mem_mapping_t mapping;

uint32_t multiboot2_magic;
uintptr_t multiboot2_addr;

__unused void _preinit()
{
	terminal_initialize();
	multiboot2_addr += 0xC0000000;

	if (multiboot2_magic != MULTIBOOT2_BOOTLOADER_MAGIC)
		kpanic("Invalid magic number: %x", multiboot2_magic);
	if (multiboot2_addr & 7)
		kpanic("Invalid address: %x", multiboot2_addr);

	struct multiboot_tag *tag = (struct multiboot_tag *)(multiboot2_addr + 8);
	while (tag->type != MULTIBOOT_TAG_TYPE_END)
	{
		if (tag->type == MULTIBOOT_TAG_TYPE_MMAP)
		{
			mapping.mmap = (struct multiboot_tag_mmap *)tag;
			mapping.nb = tag->size / mapping.mmap->entry_size;
			return;
		}
		tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7));
	}

	// Shouldn't happen
	kpanic("No memory map found");
}
