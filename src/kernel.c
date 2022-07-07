#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "CPU/mode.h"
#include "IO/terminal.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most likely run into trouble"
#endif

#if !defined(__i386__)
#error "You must compile for i386"
#endif

size_t strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_writestring(const char *data)
{
	terminal_write(data, strlen(data));
}

void terminal_motd(void)
{
	terminal_writestring("        :::      :::::::::\n");
	terminal_writestring("       :+:      :+:    :+:\n");
	terminal_writestring("     +:+ +:+         +:+  \n");
	terminal_writestring("   +#+  +:+       +#+     \n");
	terminal_writestring(" +#+#+#+#+#+   +#+        \n");
	terminal_writestring("      #+#    #+#          \n");
	terminal_writestring("     ###   ########.kfs   \n");
	terminal_writestring("By gboucett\n");
}

int main(void)
{
	cli();
	terminal_initialize();
	terminal_motd();

	sti();
	return 0;
}
