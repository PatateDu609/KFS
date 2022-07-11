#include "IO/terminal.h"
#include "CPU/port.h"
#include "IO/write.h"
#include "IO/printk.h"
#include <string.h>

bool prompt = false;

terminal_t terminal[12];
uint8_t term_cur = 0;
uint16_t *terminal_buffer = (uint16_t *)0xB8000;

void terminal_motd(void)
{
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	if (!term_cur)
	{
		printk("        :::      :::::::::\n");
		printk("       :+:      :+:    :+:\n");
		printk("     +:+ +:+         +:+  \n");
		printk("   +#+  +:+       +#+     \n");
		printk(" +#+#+#+#+#+   +#+        \n");
		printk("      #+#    #+#          \n");
		printk("     ###   ########.kfs   ");
		terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
		printk("By gboucett\n\n");
	}
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
	printk("This is TTY%d\n\n", term_cur);
}

void terminal_initialize(void)
{
	int size = sizeof(terminal) / sizeof(terminal_t);
	for (int i = 0; i < size; i++)
	{
		terminal[i].row = 0;
		terminal[i].column = 0;
		terminal[i].color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		terminal[i].is_initialized = false;

		for (size_t y = 0; y < VGA_HEIGHT; y++)
		{
			for (size_t x = 0; x < VGA_WIDTH; x++)
			{
				const size_t index = y * VGA_WIDTH + x;
				uint16_t entry = vga_entry(' ', terminal[i].color);
				terminal[i].buffer[index] = entry;
			}
		}
	}

	disable_cursor();

	terminal[term_cur].is_initialized = true;
	memcpy(terminal_buffer, terminal[term_cur].buffer, VGA_WIDTH * VGA_HEIGHT * sizeof(uint16_t));

	enable_cursor(0, 0);
}
