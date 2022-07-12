#include "CPU/IDT.h"
#include "IO/printk.h"
#include "panic.h"
#include <stdbool.h>

#include <signal.h>

enum Type
{
	FAULT,
	TRAP,
	ABORT,
	INTERRUPT,
};

struct
{
	enum Type type;

	uint8_t vec;
	const char *desc;
	bool need_error;
	int8_t signal;
} isr_err[] = {
	{FAULT, 0, "Division By Zero", false, SIGFPE},
	{TRAP, 1, "Debug", false, SIGTRAP},
	{INTERRUPT, 2, "Non Maskable Interrupt", false, -1},
	{TRAP, 3, "Breakpoint", false, SIGTRAP},
	{TRAP, 4, "Overflow", false, -1},
	{FAULT, 5, "Bound Range Exceeded", false, SIGSEGV},
	{FAULT, 6, "Invalid Opcode", false, SIGILL},
	{FAULT, 7, "Device Not Available", false, -1},
	{ABORT, 8, "Double Fault", true, -1},
	{FAULT, 9, "Coprocessor Segment Overrun", false, -1},
	{FAULT, 10, "Invalid TSS", true, -1},
	{FAULT, 11, "Segment Not Present", true, -1},
	{FAULT, 12, "Stack Fault", true, -1},
	{FAULT, 13, "General Protection Fault", true, SIGSEGV},
	{FAULT, 14, "Page Fault", true, SIGSEGV},
	{FAULT, 16, "x87 FPU Floating-Point Error", false, SIGFPE},
	{FAULT, 17, "Alignment Check", true, -1},
	{ABORT, 18, "Machine Check", false, -1},
	{FAULT, 19, "SIMD Floating-Point Exception", false, SIGFPE},
	{FAULT, 20, "Virtualization Exception", false, -1},
	{FAULT, 21, "Control Protection Exception", true, -1},
	{FAULT, 28, "Hypervisor Injection Exception", false, -1},
	{FAULT, 29, "VMM Communication Exception", true, -1},
	{FAULT, 30, "Security Exception", true, -1},
};

void exception_handler(int vec)
{
	int size = sizeof isr_err / sizeof isr_err[0];
	for (int i = 0; i < size; i++)
	{
		if (isr_err[i].vec == vec)
		{
			if (isr_err[i].type != ABORT)
				printk("%s\n", isr_err[i].desc);
			else
				kpanic("%s", isr_err[i].desc);
			break;
		}
	}
}
