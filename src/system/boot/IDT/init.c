#include "CPU/GDT.h"
#include "CPU/IDT.h"
#include "CPU/PIC.h"
#include "CPU/port.h"

__aligned(16) static struct idt_entry idt[IDT_ENTRIES];

extern void *isr_stub_table[];

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags)
{
	idt[vector].base_lo = (uint32_t)isr & 0xFFFF;
	idt[vector].seg_selector = KMCS;
	idt[vector].flags = flags;
	idt[vector].base_hi = (uint32_t)isr >> 16;
	idt[vector].reserved = 0;
}

void init_idt(void)
{
	struct idt_ptr idtr;
	idtr.limit = sizeof(idt) - 1;
	idtr.base = (uint32_t)idt;

	for (uint8_t i = 0; i < 32; i++)
		idt_set_descriptor(i, isr_stub_table[i], 0x8E);

	idt_set_descriptor(0x21, keyboard_handler, 0x8E);

	load_idt(&idtr);

	outb(PIC1_DATA, 0xFD);
}
