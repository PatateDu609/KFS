#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "CPU/mode.h"
#include "IO/terminal.h"
#include "IO/write.h"
#include "IO/read.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most likely run into trouble"
#endif

#if !defined(__i386__)
#error "You must compile for i386"
#endif

void terminal_motd(void)
{
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK));
	terminal_writestring("        :::      :::::::::\n");
	terminal_writestring("       :+:      :+:    :+:\n");
	terminal_writestring("     +:+ +:+         +:+  \n");
	terminal_writestring("   +#+  +:+       +#+     \n");
	terminal_writestring(" +#+#+#+#+#+   +#+        \n");
	terminal_writestring("      #+#    #+#          \n");
	terminal_writestring("     ###   ########.kfs   ");
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
	terminal_writestring("By gboucett\n\n");
}

int main(void)
{
	cli();
	terminal_initialize();
	terminal_motd();

	sti();
	readline(NULL, 0);
	return 0;
}
