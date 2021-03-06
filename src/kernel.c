#include <stdbool.h>
#include <stddef.h>

#include "CPU/GDT.h"
#include "IO/terminal.h"

#if defined(__linux__)
#warning "You are not using a cross-compiler, you will most likely run into trouble"
#endif

#if !defined(__i386__)
#error "You must compile for i386"
#endif

int main(void)
{
	terminal_motd();

	prompt = true;
	terminal_prompt();

	while (true)
		asm("hlt");
	return 0;
}
