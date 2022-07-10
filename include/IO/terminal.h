#ifndef IO_TERMINAL_H
#define IO_TERMINAL_H

#include "../libc/stdint.h"
#include <stddef.h>
#include <stdbool.h>

#ifndef PS1
#define PS1 "KFS > "
#endif

extern bool prompt;

enum vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef struct
{
	uint16_t buffer[VGA_HEIGHT * VGA_WIDTH];

	uint8_t column;
	uint8_t row;
	uint8_t multiline;

	uint8_t color;

	bool is_initialized;
} terminal_t;

extern terminal_t terminal[12];
extern uint16_t* terminal_buffer;
extern uint8_t term_cur;

void terminal_initialize(void);
void terminal_motd(void);
void terminal_move(size_t x, size_t y);

void terminal_entry(unsigned char c);
void terminal_putchar(char c);

void enable_cursor(uint8_t start, uint8_t end);
void disable_cursor(void);
void move_cursor(uint8_t x, uint8_t y);
void get_cursor_position(uint8_t *x, uint8_t *y);

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
uint16_t vga_entry(unsigned char uc, uint8_t color);
void terminal_setcolor(uint8_t color);

void terminal_prompt(void);

#endif
