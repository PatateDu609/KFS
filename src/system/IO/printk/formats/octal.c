#include "IO/printk.h"

int print_octal(va_list *arg, directive_args_t *fmt)
{
	char buffer[25];
	setup_buffer_base(arg, fmt->cast, buffer, sizeof buffer, "01234567");

	return printk_putstr(buffer, fmt, true);
}
