#include "CPU/GDT.h"
#include <stddef.h>
#include "IO/printk.h"
#include "IO/terminal.h"

static void fixed_print(uint8_t c)
{
	uint8_t u = c & 0x0F;
	uint8_t d = (c & 0xF0) >> 4;
	char *hex = "0123456789ABCDEF";

	printk("%c%c ", hex[d], hex[u]);
}

void print_stack(void *sp, void *sf)
{
	uint8_t color;

	// Print a hex dump of the stack.
	size_t i = 0;
	while (sp < sf)
	{
		if (i % 16 == 0)
		{
			color = vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK);
			terminal_setcolor(color);
			printk("%p: ", sp);
			color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
			terminal_setcolor(color);
		}
		fixed_print(*(uint8_t *)sp);
		sp++;
		i++;
		if (i % 16 == 0)
		{
			terminal_putchar('\n');
		}
	}
	printk("\n\n");
}
