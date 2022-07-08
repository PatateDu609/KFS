#include "IO/terminal.h"
#include "CPU/interrupts.h"

void enable_cursor(uint8_t start, uint8_t end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

void disable_cursor(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void move_cursor(uint8_t x, uint8_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void get_cursor_position(uint8_t *x, uint8_t *y)
{
	uint16_t pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= (uint16_t)(inb(0x3D5) << 8);

	*y = (uint8_t)(pos / VGA_WIDTH);
	*x = (uint8_t)(pos % VGA_WIDTH);
}
