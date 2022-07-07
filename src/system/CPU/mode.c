#include "CPU/mode.h"

void cli()
{
	asm volatile("cli");
}

void sti()
{
	asm volatile("sti");
}
