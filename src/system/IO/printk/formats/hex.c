#include "IO/printk.h"
#include <string.h>

void printk_to_str_base(uint64_t value, char *buffer, size_t max, char *base)
{
	int b = strlen(base);

	for (size_t i = 0; i < max; i++)
	{
		int digit = value % b;
		buffer[i] = base[digit];
		value /= b;
		if (value == 0)
		{
			max = i + 1;
			break;
		}
	}

	// Reverse the string (max is the last i that was set)
	for (size_t i = 0; i < max / 2; i++)
	{
		char tmp = buffer[i];
		buffer[i] = buffer[max - i - 1];
		buffer[max - i - 1] = tmp;
	}
}

void setup_buffer_base(va_list *args, uint8_t cast, char *buffer, size_t s, char *base)
{
	if (cast == PRINTK_CAST_HALFWORD)
		CAST_BASE(args, uint32, buffer, s, base)
	else if (cast == PRINTK_CAST_DOUBLEWORD)
		CAST_BASE(args, uint64, buffer, s, base)
	else if (cast == PRINTK_CAST_BYTE)
		CAST_BASE(args, uint32, buffer, s, base)
	else
		CAST_BASE(args, uint32, buffer, s, base)
}

int print_hex(va_list *args, directive_args_t *fmt)
{
	char buffer[20];
	char *base = fmt->type == 'x' ? "0123456789abcdef" : "0123456789ABCDEF";
	setup_buffer_base(args, fmt->cast, buffer, sizeof buffer, base);

	return printk_putstr(buffer, fmt, true);
}

/*
	base_addr = 0x0, length = 0x9fc00, available RAM
	base_addr = 0x9fc00, length = 0x400, reserved RAM
	base_addr = 0xf0000, length = 0x10000, reserved RAM
	base_addr = 0x100000, length = 0x7ee0000, available RAM
	base_addr = 0x7fe0000, length = 0x20000, reserved RAM
	base_addr = 0xfffc0000, length = 0x40000, reserved RAM
*/
