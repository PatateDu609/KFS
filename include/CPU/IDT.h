#ifndef CPU_IDT_H
#define CPU_IDT_H

#include "../libc/stdint.h"
#include "../utils.h"

#define IDT_ENTRIES 256

#define KBD_DATA_PORT 0x60	 // Read/Write
#define KBD_STATUS_PORT 0x64 // Read-only
#define KBD_CMD_PORT 0x64	 // Write-only

struct idt_entry
{
	uint16_t base_lo;
	uint16_t seg_selector;
	uint8_t reserved;
	uint8_t flags;
	uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void load_idt(struct idt_ptr *idtr);

__noreturn void exception_handler(void);

void keyboard_handler(void);

#endif
