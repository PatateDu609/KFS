#include "IO/terminal.h"

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
