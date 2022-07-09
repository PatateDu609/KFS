#include "IO/terminal.h"
#include "CPU/port.h"

static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n')
	{
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	else
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH)
		{
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}
	move_cursor(terminal_column, terminal_row);
}

char terminal_getchar(void)
{
	char res = 0;

	while (!res)
	{
		if (inb(0x64) & 0x1)
		{
			res = inb(0x60);
			if (res == '\n')
				res = '\n';
		}
	}
	terminal_putchar(res);
	return res;
}

void terminal_move(size_t x, size_t y)
{
	terminal_column = x;
	terminal_row = y;
	move_cursor(terminal_column, terminal_row);
}
