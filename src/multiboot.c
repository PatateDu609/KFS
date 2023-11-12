#include "multiboot2.h"
#include <stdint.h>
#include "IO/terminal.h"
#include "panic.h"
#include "mem/physical.h"

mem_mapping_t mapping;

__unused void _preinit(__unused int magic, __unused uintptr_t addr)
{
	terminal_initialize();

//	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
//		kpanic("Invalid magic number: %x", magic);
//	if (addr & 7)
//		kpanic("Invalid address: %x", addr);
//
//	struct multiboot_tag *tag = (struct multiboot_tag *)(addr + 8);
//	while (tag->type != MULTIBOOT_TAG_TYPE_END)
//	{
//		if (tag->type == MULTIBOOT_TAG_TYPE_MMAP)
//		{
//			mapping.mmap = (struct multiboot_tag_mmap *)tag;
//			mapping.nb = tag->size / mapping.mmap->entry_size;
//			return;
//		}
//		tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag + ((tag->size + 7) & ~7));
//	}
//
//	// Shouldn't happen
//	kpanic("No memory map found");
}
