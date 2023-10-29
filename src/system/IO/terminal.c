#include "IO/terminal.h"
#include "IO/write.h"
#include "IO/keyboard.h"
#include <string.h>
#include <ctype.h>
#include "nanoshell/shell.h"

#define TAB_SIZE 4

static size_t PS1_end = 0;
static char command[COMMAND_LENGTH_MAX];
static int index = 0;

static void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t idx = y * VGA_WIDTH + x;
	terminal_buffer[idx] = vga_entry(c, color);
}

void terminal_prompt(void)
{
	if (!prompt)
		return;

	uint8_t color = vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);
	terminal_setcolor(color);
	terminal_writestring(PS1);
	PS1_end = terminal[term_cur].column;

	color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_setcolor(color);
}

static void terminal_update_cursor(unsigned char c)
{
	if (c == LEFT && terminal[term_cur].column > PS1_end)
		terminal[term_cur].column--;
	if (c == RIGHT && terminal[term_cur].column < VGA_WIDTH - 1)
		terminal[term_cur].column++;

	terminal_move(terminal[term_cur].column, terminal[term_cur].row);
}

static void terminal_screen(unsigned char c)
{
	int size = VGA_WIDTH * VGA_HEIGHT * sizeof(uint16_t);

	memcpy(terminal[term_cur].buffer, terminal_buffer, size);
	term_cur = GET_F(c);
	memcpy(terminal_buffer, terminal[term_cur].buffer, size);

	if (terminal[term_cur].is_initialized)
	{
		terminal_setcolor(terminal[term_cur].color);
		terminal_move(terminal[term_cur].column, terminal[term_cur].row);
	}
	else
	{
		prompt = false;
		terminal_motd();
		prompt = true;
		terminal_prompt();
		terminal[term_cur].is_initialized = true;
	}
}

void terminal_entry(unsigned char c)
{
	if (isprint(c) || c == '\n' || c == '\b')
	{
		if (c == '\n')
		{
			command[index] = '\0';
			prompt = false;
			terminal_putchar('\n');
			execute(command);
			prompt = true;
			terminal_prompt();
			index = 0;
			return ;
		}
		else if (c != '\n' && c != '\b')
			command[index++] = (char)c;
		else if (c == '\b')
		{
			if (index > 0)
				index--;
		}
		terminal_putchar((char)c);
	}
	if (c == UP || c == DOWN || c == LEFT || c == RIGHT)
		terminal_update_cursor(c);
	if (IS_F(c))
		terminal_screen(c);
}

static void terminal_scroll(void)
{
	int size = VGA_WIDTH * sizeof(uint16_t);

	for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
	{
		uint16_t *dst = terminal_buffer + y * VGA_WIDTH; // Scroll up
		uint16_t *src = dst + VGA_WIDTH;
		memcpy(dst, src, size);
	}
	for (size_t x = 0; x < VGA_WIDTH; x++)
	{
		terminal_putentryat(' ', terminal[term_cur].color, x, VGA_HEIGHT - 1);
	}

	terminal[term_cur].row = VGA_HEIGHT - 1;
}

static void terminal_manage_multiline(uint8_t new_col) {
	++terminal[term_cur].multiline;
	PS1_end = 0;
	terminal[term_cur].column = new_col;
	if (++terminal[term_cur].row == VGA_HEIGHT)
		terminal_scroll();
}

void terminal_putchar(char c)
{
	if (!c)
		return;
	if (c == '\n')
	{
		terminal[term_cur].multiline = 0;
		terminal[term_cur].column = 0;
		if (++terminal[term_cur].row == VGA_HEIGHT)
			terminal_scroll();
	}
	else if (c == '\t')
	{
		terminal[term_cur].multiline = 0;
		terminal[term_cur].column += TAB_SIZE;
		if (terminal[term_cur].column >= VGA_WIDTH)
		{
			terminal_manage_multiline(TAB_SIZE);
		}
	}
	else if (c == '\b')
	{
		if (terminal[term_cur].column > PS1_end)
			terminal[term_cur].column--;
		else if (terminal[term_cur].multiline && terminal[term_cur].row > 0)
		{
			terminal[term_cur].multiline--;
			if (terminal[term_cur].multiline == 0)
				PS1_end = strlen(PS1);
			terminal[term_cur].row--;
			terminal[term_cur].column = VGA_WIDTH - 1;
		}
		terminal_putentryat(' ',
			terminal[term_cur].color,
			terminal[term_cur].column,
			terminal[term_cur].row);
	}
	else
	{
		terminal_putentryat(c,
			terminal[term_cur].color,
			terminal[term_cur].column,
			terminal[term_cur].row);

		if (++terminal[term_cur].column == VGA_WIDTH)
		{
			terminal_manage_multiline(0);
		}
	}
	move_cursor(terminal[term_cur].column, terminal[term_cur].row);

	if (c == '\n')
		terminal_prompt();
}

void terminal_move(size_t x, size_t y)
{
	terminal[term_cur].column = x;
	terminal[term_cur].row = y;
	move_cursor(terminal[term_cur].column, terminal[term_cur].row);
}

void terminal_clear(void)
{
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			terminal_putentryat(' ', terminal[term_cur].color, x, y);

	terminal[term_cur].column = 0;
	terminal[term_cur].row = 0;
	terminal[term_cur].multiline = 0;
	PS1_end = strlen(PS1);
	move_cursor(terminal[term_cur].column, terminal[term_cur].row);
}
