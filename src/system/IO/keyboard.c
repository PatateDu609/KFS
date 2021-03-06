#include "IO/keyboard.h"
#include <stdbool.h>

// Scan codes for the keyboard (set 1).
static unsigned char PRESSED_SC[] = {
	// Extended scan codes.
	[0xE0] = EXT,

	// Numbers
	[0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4', [0x06] = '5',
	[0x07] = '6', [0x08] = '7', [0x09] = '8', [0x0A] = '9', [0x0B] = '0',
	// Symbols
	[0x0C] = '-', [0x0D] = '=', [0x35] = '/', [0x1A] = '[', [0x1B] = ']',
	[0x2B] = '\\', [0x27] = ';', [0x28] = '\'', [0x29] = '`', [0x33] = ',',
	[0x34] = '.',
	// Whitespaces and backspace
	[0x39] = ' ', [0x0F] = '\t', [0x1C] = '\n', [0x0E] = BACKSPACE,
	// Letters
	[0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r', [0x14] = 't',
	[0x15] = 'y', [0x16] = 'u', [0x17] = 'i', [0x18] = 'o', [0x19] = 'p',
	[0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f', [0x22] = 'g',
	[0x23] = 'h', [0x24] = 'j', [0x25] = 'k', [0x26] = 'l', [0x2C] = 'z',
	[0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v', [0x30] = 'b', [0x31] = 'n',
	[0x32] = 'm',
	// Control
	[0x01] = ESC, [0x1D] = CTRL_L, [0x2A] = SHIFT_L, [0x36] = SHIFT_R,
	// F-keys
	[0x3B] = F1, [0x3C] = F2, [0x3D] = F3, [0x3E] = F4, [0x3F] = F5,
	[0x40] = F6, [0x41] = F7, [0x42] = F8, [0x43] = F9, [0x44] = F10,
	[0x57] = F11, [0x58] = F12,
	// TODO: Add keypad support.
};

static unsigned char PRESSED_EXT_SC[] = {
	// Control
	[0x1D] = CTRL_R, [0x38] = ALT_R, [0x53] = 127,
	// Arrows
	[0x48] = UP, [0x50] = DOWN, [0x4B] = LEFT, [0x4D] = RIGHT,
};

unsigned char getch(int keycode)
{
	static bool extended = false;
	unsigned char key = extended ? PRESSED_EXT_SC[keycode] : PRESSED_SC[keycode];

	if (key == EXT && !extended)
	{
		extended = true;
		return NOT_FOUND;
	}
	if (extended)
		extended = false;
	if (key)
		return key;
	return NOT_FOUND;
}
