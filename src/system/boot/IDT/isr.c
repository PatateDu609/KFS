#include "CPU/IDT.h"

void exception_handler(void)
{
	asm volatile("cli; hlt");
	__unreachable
}
