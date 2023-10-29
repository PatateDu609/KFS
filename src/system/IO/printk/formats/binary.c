#include "IO/printk.h"

int print_binary(va_list arg, directive_args_t *fmt)
{
	char buffer[65];
	setup_buffer_base(arg, fmt->cast, buffer, sizeof buffer, "01");

	return printk_putstr(buffer, fmt, true);
}
