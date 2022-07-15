#include "memory/probe.h"
#include <stdint.h>
#include <stddef.h>
#include "IO/terminal.h"
#include "panic.h"

multiboot_info_t *_mbd;

void _preinit(int magic, multiboot_info_t *mbd)
{
	terminal_initialize();
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		kpanic("Invalid magic number: %x", magic);
	if (!(mbd->flags & MULTIBOOT_INFO_MEM_MAP))
		kpanic("Invalid memory map provided by grub");

	for (uint32_t i = 0;
		 i < mbd->mmap_length;
		 i += sizeof(multiboot_memory_map_t))
	{
		multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)(mbd->mmap_addr + i);

		if (!_mbd && mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
			_mbd = mbd;
	}

	if (!_mbd)
		kpanic("No available memory found");
}
