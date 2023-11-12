#include "CPU/GDT.h"
#include <string.h>

static uint64_t create_entry(uint32_t base, uint32_t limit, uint16_t flags) {
	uint64_t descriptor;

	descriptor = limit & 0x000F0000;         // set limit bits 19:16
	descriptor |= (flags << 8) & 0x00F0FF00; // set type, p, dpl, s, g, d/b, l and avl fields
	descriptor |= (base >> 16) & 0x000000FF; // set base bits 23:16
	descriptor |= base & 0xFF000000;         // set base bits 31:24

	// shift to the right by 4 to allow modification of the lower bytes
	descriptor <<= 32;

	descriptor |= base << 16;          // set base bits 15:0
	descriptor |= limit & 0x0000FFFF; // set limit bits 15:0

	return descriptor;
}

static uint64_t gdt[7];
struct gdtr *gdtr = (struct gdtr *) GDT_ADDR;

void init_gdt(void) {
	uint64_t gdt_tmp[] = {
			create_entry(0, 0, 0),
			create_entry(0, 0xFFFFF, GDT_CODE_PL0),     // kernel code (offset KMCS = 0x08)
			create_entry(0, 0xFFFFF, GDT_DATA_PL0),     // kernel data (offset 0x10)
			create_entry(0, 0xFFFFF, GDT_STACK_PL0),    // kernel stack (offset 0x18)
			create_entry(0, 0xBFFFF, GDT_CODE_PL3),     // user code (offset 0x20)
			create_entry(0, 0xBFFFF, GDT_DATA_PL3),     // user data (offset 0x28)
			create_entry(0, 0xBFFFF, GDT_STACK_PL3),    // user stack (offset 0x30)
	};

	memcpy(gdt, gdt_tmp, sizeof(gdt_tmp));

	gdtr->base = (uint32_t) gdt;
	gdtr->limit = sizeof(gdt) - 1;
	load_gdt(gdtr);
}
