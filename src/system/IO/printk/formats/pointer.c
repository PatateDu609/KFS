#include "IO/printk.h"
#include "utils.h"
#include <string.h>

int print_pointer(va_list *arg, directive_args_t *fmt)
{
	uint32_t value = va_arg(*arg, uint32_t);
	char buffer[22];
	if (value == 0)
		memcpy(buffer, "(null)", 6);
	else
		printk_to_str_base(value, buffer, sizeof buffer, "0123456789abcdef");

	memcpy(buffer, "0x", 2);
	printk_to_str_base(value, buffer + 2, sizeof buffer - 2, "0123456789abcdef");

	return printk_putstr(buffer, fmt, true);
}
