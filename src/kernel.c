#include <stdbool.h>
#include <stddef.h>

#include "CPU/mode.h"
#include "IO/terminal.h"
#include "IO/write.h"
#include "IO/printk.h"

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
	printk("       :+:      :+:    :+:\n");
	printk("     +:+ +:+         +:+  \n");
	printk("   +#+  +:+       +#+     \n");
	printk(" +#+#+#+#+#+   +#+        \n");
	printk("      #+#    #+#          \n");
	printk("     ###   ########.kfs   ");
	terminal_setcolor(vga_entry(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK));
	terminal_writestring("By gboucett\n\n");
}

int main(void)
{
	terminal_motd();
	printk("%c %s for KFS %u\n", 'A', "Basical prompt", 10);

	while (true)
		asm("hlt");
	return 0;
}
