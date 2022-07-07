#include "IO/read.h"
#include "IO/terminal.h"
#include "IO/write.h"
#include "utils.h"

const char *prompt = "kfs-gboucett # > ";

static void terminal_read(__unused char *buffer, __unused size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		char c = terminal_getchar();
		terminal_putchar(c);

		if (c == '\n')
		{
			buffer[i] = '\0';
			return;
		}

		buffer[i] = c;
		i++;
	}
}

void readline(char *buffer, size_t size)
{
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
	terminal_writestring(prompt);
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

	terminal_read(buffer, size);
}
