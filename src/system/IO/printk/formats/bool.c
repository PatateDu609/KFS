#include "IO/printk.h"
#include <string.h>

int print_bool(va_list *arg, directive_args_t *fmt)
{
	bool value = va_arg(*arg, int);

	char buffer[20];
	if (value)
		strcpy(buffer, "true");
	else
		strcpy(buffer, "false");
	return printk_putstr(buffer, fmt, true);
}
